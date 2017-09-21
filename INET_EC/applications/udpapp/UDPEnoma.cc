/* Created by Larry */

#include "inet/applications/udpapp/UDPEnoma.h"

#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/base/EnomaPackage_m.h"
#include "inet/applications/optimize/enomaOptimize.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/NodeOperations.h"
#include "inet/transportlayer/contract/udp/UDPControlInfo_m.h"
#include "inet/networklayer/ipv4/IIPv4ServiceTable.h"
#include "inet/networklayer/ipv4/IPv4Service.h"



namespace inet {

Define_Module(UDPEnoma);

simsignal_t UDPEnoma::sentPkSignal = registerSignal("sentPk");
simsignal_t UDPEnoma::rcvdPkSignal = registerSignal("rcvdPk");


UDPEnoma::~UDPEnoma()
{
    cancelAndDelete(selfMsg);
}

void UDPEnoma::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);

        localPort = par("localPort");
        destPort = par("destPort");
        startTime = par("startTime").doubleValue();
        stopTime = par("stopTime").doubleValue();
        packetName = par("packetName");
        isEnoma = par("isEnoma");
        isEdgeNode = par("isEdgeNode");

        if(isEnoma == 1){
            processTopology();
        }

        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("sendTimer");


    }
}

void UDPEnoma::finish()
{
    recordScalar("packets sent", numSent);
    recordScalar("packets received", numReceived);
    ApplicationBase::finish();
}

void UDPEnoma::setSocketOptions()
{
    int timeToLive = par("timeToLive");
    if (timeToLive != -1)
        socket.setTimeToLive(timeToLive);

    int typeOfService = par("typeOfService");
    if (typeOfService != -1)
        socket.setTypeOfService(typeOfService);

    const char *multicastInterface = par("multicastInterface");
    if (multicastInterface[0]) {
        IInterfaceTable *ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        InterfaceEntry *ie = ift->getInterfaceByName(multicastInterface);
        if (!ie)
            throw cRuntimeError("Wrong multicastInterface setting: no interface named \"%s\"", multicastInterface);
        socket.setMulticastOutputInterface(ie->getInterfaceId());
    }

    bool receiveBroadcast = par("receiveBroadcast");
    if (receiveBroadcast)
        socket.setBroadcast(true);

    bool joinLocalMulticastGroups = par("joinLocalMulticastGroups");
    if (joinLocalMulticastGroups) {
        MulticastGroupList mgl = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this)->collectMulticastGroups();
        socket.joinLocalMulticastGroups(mgl);
    }
}

L3Address UDPEnoma::chooseDestAddr()
{
    int k = intrand(destAddresses.size());
    if (destAddresses[k].isLinkLocal()) {    // KLUDGE for IPv6
        const char *destAddrs = par("destAddresses");
        cStringTokenizer tokenizer(destAddrs);
        const char *token = nullptr;

        for (int i = 0; i <= k; ++i)
            token = tokenizer.nextToken();
        destAddresses[k] = L3AddressResolver().resolve(token);
    }
    return destAddresses[k];
}

void UDPEnoma::sendPacket()
{
    std::ostringstream str;
    str << packetName << "-" << numSent;
    ApplicationPacket *payload = new ApplicationPacket(str.str().c_str());
    payload->setByteLength(par("messageLength").longValue());
    payload->setSequenceNumber(numSent);

    L3Address destAddr = chooseDestAddr();

    emit(sentPkSignal, payload);
    socket.sendTo(payload, destAddr, destPort);
    numSent++;
}

void UDPEnoma::processTopology()
{
    topology = par("topology");

    cXMLElementList edgeElements = topology->getChildrenByTagName("edge");
    for (auto & edgeElement : edgeElements) {
        const char *edgeName = edgeElement->getAttribute("name");
        const char *net = edgeElement->getAttribute("net");
        EV << "LARRY ~~~ " << edgeName << "-" << net <<"\n";
        stable st = stable();
        strcpy(st.node, edgeName);
        strcpy(st.child[0], net);
        topo_edges.push_back(st);

        //Initialize Edge table for optimize
        stable ost = stable();
        strcpy(ost.node, edgeName);
        opt_edges.push_back(ost);
    }

    cXMLElementList rgElements = topology->getChildrenByTagName("RG");
    for (auto & rgElement : rgElements) {
        const char *rgName = rgElement->getAttribute("name");
        const char *net = rgElement->getAttribute("net");
        EV << "LARRY ~~~ " << rgName << "-" << net <<"\n";

        //Traverse each service in service List
        std::istringstream ss(net);
        std::string token;
        stable st = stable();
        strcpy(st.node, rgName);
        int cnt = 0;
        while(std::getline(ss, token, ',')) {
            EV << "LARRY ~~~ " << token <<"\n";
            strcpy(st.child[cnt], token.c_str());
            cnt++;
        }
        topo_rgs.push_back(st);

        //Initialize RG table for optimize
        stable ost = stable();
        strcpy(ost.node, rgName);
        opt_rgs.push_back(ost);
    }

    cXMLElementList coreElements = topology->getChildrenByTagName("Core");
    for (auto & coreElement : coreElements) {
        const char *coreName = coreElement->getAttribute("name");
        const char *net = coreElement->getAttribute("net");
        EV << "LARRY ~~~ " << coreName << "-" << net <<"\n";

        //Traverse each service in service List
        std::istringstream ss(net);
        std::string token;
        stable st = stable();
        strcpy(st.node, coreName);
        int cnt = 0;
        while(std::getline(ss, token, ',')) {
            EV << "LARRY ~~~ " << token <<"\n";
            strcpy(st.child[cnt], token.c_str());
            cnt++;
        }
        topo_cores.push_back(st);

        //Initialize RG table for optimize
        stable ost = stable();
        strcpy(ost.node, coreName);
        opt_cores.push_back(ost);
    }

}

void UDPEnoma::processStart()
{
    socket.setOutputGate(gate("udpOut"));
    const char *localAddress = par("localAddress");
    socket.bind(*localAddress ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
    setSocketOptions();

    const char *destAddrs = par("destAddresses");
    cStringTokenizer tokenizer(destAddrs);
    const char *token;

    while ((token = tokenizer.nextToken()) != nullptr) {
        L3Address result;
        L3AddressResolver().tryResolve(token, result);
        if (result.isUnspecified())
            EV_ERROR << "cannot resolve destination address: " << token << endl;
        else
            destAddresses.push_back(result);
    }

    if (!destAddresses.empty()) {
        selfMsg->setKind(SEND);
        processSend();
    }
    else {
        if (stopTime >= SIMTIME_ZERO) {
            selfMsg->setKind(STOP);
            scheduleAt(stopTime, selfMsg);
        }
    }

    if (isEnoma == 1){
        processOptimize();
    }
}

void UDPEnoma::processOptimize()
{
    //TODO: Optimize here
    //enomaOptimize eO = enomaOptimize();
    //eO.doOptimize();

    runOptimizeTest();

    //Schedule to optimize again periodically
    simtime_t d = simTime() + par("sendIntervalOptimize").doubleValue();
    selfMsg->setKind(OPTIMIZE);
    scheduleAt(d, selfMsg);
}

void UDPEnoma::processSend()
{
    sendPacket();
    simtime_t d = simTime() + par("sendInterval").doubleValue();
    if (stopTime < SIMTIME_ZERO || d < stopTime) {
        selfMsg->setKind(SEND);
        scheduleAt(d, selfMsg);
    }
    else {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}

void UDPEnoma::processStop()
{
    socket.close();
}

char* UDPEnoma::getEdgeFromUe(const char* ueIp)
{
    int size = topo_edges.size();
    for (int i = 0; i < size; i++) {
        EV << "LARRY ~~~ topo_edges[i].child[0] = " << topo_edges[i].child[0] << "\n";
        //Compare 192.168.0.1 & 192.168.0.0
        std::istringstream ss1(topo_edges[i].child[0]);
        std::istringstream ss2(ueIp);
        std::string token1, token2;
        int cnt = 0;
        while(std::getline(ss1, token1, '.') && std::getline(ss2, token2, '.')) {
            EV << "LARRY ~~~ " << token1 << token2 << "\n";
            cnt++;
            if(strcmp(token1.c_str(), token2.c_str()) != 0)
                break;//if different -> break

            if(cnt == 3) //check 3 netmask xxx.xxx.xxx.0
                return topo_edges[i].node;
        }
    }
    return NULL;
}

char* UDPEnoma::getRgFromEdge(const char* edge)
{
    int size = topo_rgs.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < MAX; j++) {
            EV << "LARRY ~~~ topo_rgs[i].child[j] = " << topo_rgs[i].child[j] << "\n";
            if(strcmp(topo_rgs[i].child[j], edge))
            {
                return topo_rgs[i].node;
            }
        }
    }
    return NULL;
}

char* UDPEnoma::getCoreFromRg(const char* rg)
{
    int size = topo_cores.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < MAX; j++) {
            EV << "LARRY ~~~ topo_cores[i].child[j] = " << topo_cores[i].child[j] << "\n";
            if(strcmp(topo_cores[i].child[j], rg))
            {
                return topo_cores[i].node;
            }
        }
    }
    return NULL;
}

void UDPEnoma::handleMessageWhenUp(cMessage *msg)
{
    cModule *thishost = getContainingNode(this);
    EV << "LARRY ~~~ HOST " << thishost->getFullName() <<"\n";

    if (msg->isSelfMessage()) {
        ASSERT(msg == selfMsg);
        switch (selfMsg->getKind()) {
            case START:
                EV << "LARRY ~~~ case START \n";
                processStart();
                break;

            case SEND:
                EV << "LARRY ~~~ case SEND \n";
                processSend();
                break;

            case STOP:
                EV << "LARRY ~~~ case STOP \n";
                processStop();
                break;

            case OPTIMIZE:
                EV << "LARRY ~~~ case OPTIMIZE \n";
                //TODO: Optimize Cache/Edge service
                processOptimize();
                break;

            default:
                EV << "LARRY ~~~ case default \n";
                throw cRuntimeError("Invalid kind %d in self message", (int)selfMsg->getKind());
        }
    }
    else if (msg->getKind() == UDP_I_DATA) {
        // process incoming packet
        EV << "LARRY ~~~ UDP_I_DATA \n";
        processPacket(PK(msg));
    }
    else if (msg->getKind() == UDP_I_ERROR) {
        EV << "LARRY ~~~ UDP_I_ERROR \n";
        EV_WARN << "Ignoring UDP error report\n";
        delete msg;
    }
    else {
        EV << "LARRY ~~~ cRuntimeError \n";
        throw cRuntimeError("Unrecognized message (%s)%s", msg->getClassName(), msg->getName());
    }
}

void UDPEnoma::refreshDisplay() const
{
    char buf[100];
    sprintf(buf, "rcvd: %d pks\nsent: %d pks", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

int UDPEnoma::getUeIndexInRequestServiceTable(const char *ue)
{
    int size = opt_ues.size();
    for (int i = 0; i < size; i++) {
        EV << "LARRY ~~~ [getUeIndexInRequestServiceTable] opt_ues[i].node :: ue === " << opt_ues[i].node <<"::" << ue << "\n";
        //Check if exist UE in Request Service Table
        if(strcmp(opt_ues[i].node, ue) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool UDPEnoma::isExistInServiceInfoTable(const char *serviceName)
{
    int size = serviceInfoTable.size();
    for (int i = 0; i < size; i++) {
        if(strcmp(serviceInfoTable[i].name, serviceName) == 0)
        {
            return true;
        }
    }
    return false;
}

int UDPEnoma::getNodeIndexFromServiceNodeTable(const char *node)
{
    int size = service_nodes.size();
    for (int i = 0; i < size; i++) {
        if(strcmp(service_nodes[i].node, node) == 0)
        {
            return i;
        }
    }
    return -1;
}

void UDPEnoma::updateUeServiceInfo(cPacket *pk)
{
    EnomaPackage * es = (EnomaPackage*) pk;

    //EV<< "LARRY ~~~ packet : " << pk << "\n";
    //EV<< "LARRY ~~~ packet : " << es->getUeIp() << "\n";
    //EV<< "LARRY ~~~ packet : " << es->getSp() << "\n";
    //deployEdgeService(es->getUeIp(), es->getSp());

    //1 user - 1 service request at 1 time
    int ue_index = getUeIndexInRequestServiceTable(es->getUeIp());
    if(ue_index == -1){
        //not exist UE in request Service Table --> add this request
        //Initialize RG table for optimize
        stable ost = stable();
        strcpy(ost.node, es->getUeIp());
        strcpy(ost.child[0], es->getSp());
        opt_ues.push_back(ost);
    }else {
        //in this case, UE exist in table -> update "service request" from UE
        int i;
        for(i = 0; i < MAX; i++){
            if(strlen(opt_ues[ue_index].child[i]) == 0){
                break;
            }
            if(strcmp(es->getSp(), opt_ues[ue_index].child[i]) == 0){
                //Exist UE & exist service request
                break;
            }
        }
        if(i < MAX){
            //Exist UE but new service request => add new service
            strcpy(opt_ues[ue_index].child[i], es->getSp());
        }
    }
    char* edge = getEdgeFromUe(es->getUeIp());
    int index = getNodeIndexFromServiceNodeTable(edge);
    if(index >= 0) {
        bool flag = false;
        int i;
        for(i = 0; i < MAX; i++){
            if(strlen(service_nodes[index].child[i]) == 0){
                break;
            }
            if(strcmp(service_nodes[index].child[i], es->getSp()) == 0){
                //if exist service in Node
                flag = true;
                break;
            }
        }
        if((flag == false) && (i < MAX)){
            //if service exist -> add service in Node Row
            strcpy(service_nodes[index].child[i], es->getSp());
        }
    }else{
        //not exist Node in table => add node into Table
        stable ost = stable();
        strcpy(ost.node, edge);
        strcpy(ost.child[0], es->getSp());
        service_nodes.push_back(ost);
    }

    //insert service info to service Info Table
    if(isExistInServiceInfoTable(es->getSp()) == false){
        //Initialize RG table for optimize
        serviceInfo si = serviceInfo();
        strcpy(si.name, es->getSp());
        si.size = es->getSize();
        si.cacheSize = es->getCacheSize();
        si.mips = es->getMips();
        serviceInfoTable.push_back(si);
    }
}

void UDPEnoma::processPacket(cPacket *pk)
{
    emit(rcvdPkSignal, pk);
    EV_INFO << "Received packet: " << UDPSocket::getReceivedPacketInfo(pk) << endl;

    if(isEnoma == 1){
        EnomaPackage * es = (EnomaPackage*) pk;
        if(es->getMsgType() == 1){ //from SP
            //Add UE ip into optimize table
            updateUeServiceInfo(pk);
        }else if(es->getMsgType() == 3){//from Edge Node
            //Update Service Table
            int size = service_nodes.size();
            for(int i = 0; i < size; i++){
                if(strcmp(service_nodes[i].node, es->getNodeName()) == 0){
                    cStringTokenizer tokenizer(es->getListEdgeService());
                    const char *token;

                    while ((token = tokenizer.nextToken()) != nullptr) {
                        //token is service name need to be deleted in the table
                        for(int j = 0; j < MAX; j++){
                            if(strcmp(service_nodes[i].child[j], token)){
                                //delete this service from service_nodes table, and shift all service behind to up
                                for(int k = j; k < MAX-1; k++){
                                    if(strlen(service_nodes[i].child[k+1]) == 0){
                                        break;
                                    }
                                    strcpy(service_nodes[i].child[k], service_nodes[i].child[k+1]);
                                }
                            }
                        }
                    }
                }
            }

        }

    }else if(isEdgeNode == 1){
        EnomaPackage * es = (EnomaPackage*) pk;
        //Enable service on Edge node
        IIPv4ServiceTable *st = getModuleFromPar<IIPv4ServiceTable>(par("serviceTableModule"), this);
        IPv4Service *entry = new IPv4Service();
        entry->setServiceName(const_cast<char*>(es->getListEdgeService()));

        st->printServiceList();

        L3Address l3Addr;
        L3AddressResolver().tryResolve(es->getListEdgeService(), l3Addr);
        EV<< "LARRY ~~~ es->getListEdgeService() : " << es->getListEdgeService() << "\n";
        EV<< "LARRY ~~~ l3Addr : " << l3Addr << "\n";
        entry->setServiceIp(l3Addr.toIPv4());
        entry->setSize(es->getSize());
        entry->setCacheSize(es->getCacheSize());
        entry->setMips(es->getMips());
        st->addService(entry);

    }
    delete pk;
    numReceived++;
}

bool UDPEnoma::handleNodeStart(IDoneCallback *doneCallback)
{
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, selfMsg);
    }
    return true;
}

bool UDPEnoma::handleNodeShutdown(IDoneCallback *doneCallback)
{
    if (selfMsg)
        cancelEvent(selfMsg);
    //TODO if(socket.isOpened()) socket.close();
    return true;
}

void UDPEnoma::handleNodeCrash()
{
    if (selfMsg)
        cancelEvent(selfMsg);
}

void UDPEnoma::runOptimizeTest()
{
    int size = service_nodes.size();
    for (int i = 0; i < size; i++) {
        //Find Edge node near UE
        //char* edge = getEdgeFromUe(opt_ues[i].node);

        for(int j = 0; j < MAX; j++){
            if(strlen(service_nodes[i].child[j]) == 0){
                break;
            }
            deployEdgeService(service_nodes[i].node, service_nodes[i].child[j]);
        }
    }
}

void UDPEnoma::deployEdgeService(const char* edge, const char* service)
{

    //Send msg to enable Edge service at that Edge Node
    EnomaPackage *payload = new EnomaPackage("Update Edge Service on Node");
    payload->setByteLength(1);
    payload->setListEdgeService(service);
    payload->setMsgType(2);//ENOMA_REQUEST = 2
    int size = serviceInfoTable.size();
    for (int i = 0; i < size; i++) {
        if(strcmp(serviceInfoTable[i].name, service) == 0)
        {
            payload->setSize(serviceInfoTable[i].size);
            payload->setCacheSize(serviceInfoTable[i].cacheSize);
            payload->setMips(serviceInfoTable[i].mips);
            break;
        }
    }

    //EV << "LARRY ~~~ edge - service " << edge << "-"<< service << "\n";
    L3Address edgeNodeAddr = L3AddressResolver().resolve(edge);
    //EV << "LARRY ~~~ edgeNodeAddr - destPort " << edgeNodeAddr << "-" << destPort << "\n";

    socket.sendTo(payload, edgeNodeAddr, destPort);

    return;
}
} // namespace inet

