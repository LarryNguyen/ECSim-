/* Created by Larry */
#include <iostream>
#include "inet/applications/udpapp/UDPEdgeApp.h"

#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/base/EnomaPackage_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/NodeOperations.h"
#include "inet/transportlayer/contract/udp/UDPControlInfo_m.h"
#include "inet/networklayer/ipv4/IIPv4ServiceTable.h"
#include "inet/networklayer/ipv4/IPv4Service.h"

namespace inet {

Define_Module(UDPEdgeApp);

simsignal_t UDPEdgeApp::sentPkSignal = registerSignal("sentPk");
simsignal_t UDPEdgeApp::rcvdPkSignal = registerSignal("rcvdPk");


UDPEdgeApp::~UDPEdgeApp()
{
    cancelAndDelete(selfMsg);
}

void UDPEdgeApp::initialize(int stage)
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
        isSP = par("isSP");
        enomaPort = par("enomaPort");
        size = par("size");
        cacheSize = par("cacheSize");
        mips = par("mips");

        disable_service_interval = par("disable_service_interval").doubleValue();
        st = getModuleFromPar<IIPv4ServiceTable>(par("serviceTableModule"), this);

        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("sendTimer");
    }
}

void UDPEdgeApp::finish()
{
    recordScalar("packets sent", numSent);
    recordScalar("packets received", numReceived);
    ApplicationBase::finish();
}

void UDPEdgeApp::setSocketOptions()
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

L3Address UDPEdgeApp::chooseDestAddr()
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

L3Address UDPEdgeApp::getEnomaAddr()
{
    const char *destAddrs = par("enomaAddresses");
    cStringTokenizer tokenizer(destAddrs);
    const char *token = nullptr;

    token = tokenizer.nextToken();
    L3Address enomaAddress = L3AddressResolver().resolve(token);

    return enomaAddress;
}
void UDPEdgeApp::sendPacket()
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

void UDPEdgeApp::processStart()
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

    //disable_service following interval
    if(disable_service_interval > SIMTIME_ZERO){
        selfMsg->setKind(UPDATE_ST);
        processUpdateSt();
    }

}

void UDPEdgeApp::processUpdateSt()
{
    //Update Service Table

    int total = st->getNumberOfService();
    double curr_time = simTime().dbl();
    for(int i = total-1; i >= 0; i--){
        EV << "LARRY~~~ [processUpdateSt] curr_time = " << curr_time << "\n";
        EV << "LARRY~~~ [processUpdateSt] st->getLastRequestSecond(i).dbl() = " << st->getLastRequestSecond(i).dbl() << "\n";
        EV << "LARRY~~~ [processUpdateSt] disable_service_interval.dbl() = " << disable_service_interval.dbl() << "\n";
        if(( curr_time - st->getLastRequestSecond(i).dbl()) >= disable_service_interval.dbl()){
            //remove service from Service Table
            EV << "LARRY~~~ [processUpdateSt] service is deleted = " << st->getServiceAddress(i) << "\n";
            strcat (removedServiceList, st->getServiceAddress(i).str(true).c_str());
            strcat (removedServiceList, " ");
            st->deleteService(i);
        }
    }
    if(strlen(removedServiceList) > 0){
        //Send msg to Enoma to announce
        EnomaPackage *payload = new EnomaPackage("Update Edge Service Table");
        cModule *thishost = getContainingNode(this);

        payload->setByteLength(1);
        payload->setListEdgeService(removedServiceList);
        payload->setMsgType(3); //EDGE_UPDATE_ST=3
        EV << "LARRY~~~ [processUpdateSt] thishost->getFullName() = " << thishost->getFullName() << "\n";
        payload->setNodeName(thishost->getFullName());
        socket.sendTo(payload, getEnomaAddr(), enomaPort);
    }

    //Send self message to itself
    simtime_t d = simTime() + par("disable_service_interval").doubleValue();
    if (stopTime < SIMTIME_ZERO || d < stopTime) {
        selfMsg->setKind(UPDATE_ST);
        scheduleAt(d, selfMsg);
    }

}

void UDPEdgeApp::processSend()
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

void UDPEdgeApp::processStop()
{
    socket.close();
}

void UDPEdgeApp::handleMessageWhenUp(cMessage *msg)
{
    cModule *thishost = getContainingNode(this);
    EV << "LARRY ~~~ HOST " << thishost->getFullName() <<"\n";

    if (msg->isSelfMessage()) {
        ASSERT(msg == selfMsg);
        switch (selfMsg->getKind()) {
            case START:
                processStart();
                break;

            case SEND:
                processSend();
                break;

            case STOP:
                processStop();
                break;

            case UPDATE_ST:
                processUpdateSt();
                break;

            default:
                throw cRuntimeError("Invalid kind %d in self message", (int)selfMsg->getKind());
        }
    }
    else if (msg->getKind() == UDP_I_DATA) {
        // process incoming packet
        processPacket(PK(msg));
    }
    else if (msg->getKind() == UDP_I_ERROR) {
        EV_WARN << "Ignoring UDP error report\n";
        delete msg;
    }
    else {
        throw cRuntimeError("Unrecognized message (%s)%s", msg->getClassName(), msg->getName());
    }
}

void UDPEdgeApp::refreshDisplay() const
{
    char buf[100];
    sprintf(buf, "rcvd: %d pks\nsent: %d pks", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void UDPEdgeApp::processPacket(cPacket *pk)
{
    emit(rcvdPkSignal, pk);
    EV_INFO << "Received packet: " << UDPSocket::getReceivedPacketInfo(pk) << endl;

    if(isEdgeNode == 1){
        // determine its source address/port
        UDPDataIndication *ctrl = check_and_cast<UDPDataIndication *>(pk->removeControlInfo());
        L3Address srcAddress = ctrl->getSrcAddr();
        int srcPort = ctrl->getSrcPort();
        delete ctrl;

        // send back
        socket.sendTo(pk, srcAddress, srcPort);

    }else if(isSP == 1){
        // determine its source address/port
        UDPDataIndication *ctrl = check_and_cast<UDPDataIndication *>(pk->removeControlInfo());
        L3Address srcAddress = ctrl->getSrcAddr();
        int srcPort = ctrl->getSrcPort();
        delete ctrl;

        // send back
        socket.sendTo(pk, srcAddress, srcPort);


        //send to Enoma
        L3Address enomaAddress = getEnomaAddr();
        EV << "LARRY ~~~ enomaAddress " << enomaAddress << "\n";
        cModule *thishost = getContainingNode(this);

        std::ostringstream str;
        str << srcAddress << "-" << thishost->getFullName();
        EnomaPackage *payload = new EnomaPackage(str.str().c_str());
        payload->setByteLength(100);
        payload->setSp(thishost->getFullName());
        payload->setUeIp(srcAddress.str().c_str());
        payload->setSize(size);
        payload->setCacheSize(cacheSize);
        payload->setMips(mips);
        payload->setMsgType(1);//SP_REQUEST = 1

        socket.sendTo(payload, enomaAddress, enomaPort);
    }else{
        delete pk;
    }

    numReceived++;
}

bool UDPEdgeApp::handleNodeStart(IDoneCallback *doneCallback)
{
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, selfMsg);
    }
    return true;
}

bool UDPEdgeApp::handleNodeShutdown(IDoneCallback *doneCallback)
{
    if (selfMsg)
        cancelEvent(selfMsg);
    //TODO if(socket.isOpened()) socket.close();
    return true;
}

void UDPEdgeApp::handleNodeCrash()
{
    if (selfMsg)
        cancelEvent(selfMsg);
}

} // namespace inet

