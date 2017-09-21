/* Created by Larry */

#include <algorithm>
#include <sstream>
#include <vector>

#include "inet/networklayer/ipv4/IPv4ServiceTable.h"
#include "inet/common/XMLUtils.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/INETUtils.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressResolver.h"

namespace inet {

Define_Module(IPv4ServiceTable);

IPv4ServiceTable::~IPv4ServiceTable()
{
    for (auto & elem : services)
        delete elem;
}

void IPv4ServiceTable::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        // get a pointer to the host module and IInterfaceTable
        cModule *host = getContainingNode(this);
        EV << "LARRY ~~~ Service Table initialize " << stage <<"\n";
        EV << "LARRY ~~~ HOST " << host->getFullName() <<"\n";
        configuration = par("serviceConfig");

        cXMLElementList serviceElements = configuration->getChildrenByTagName("edge-service");
        for (auto & serviceElement : serviceElements) {
            const char *hostAttr = serviceElement->getAttribute("hosts");
            const char *serviceList = serviceElement->getAttribute("services");
            EV << "LARRY ~~~ " << hostAttr <<"\n";
            if(strcmp(host->getFullName(), hostAttr) == 0){
                EV << "LARRY ~~~ " << hostAttr <<"\n";
                EV << "LARRY ~~~ " << serviceList <<"\n";
                //Traverse each service in service List
                std::istringstream ss(serviceList);
                std::string token;

                while(std::getline(ss, token, ',')) {
                    EV << "LARRY ~~~ " << token <<"\n";
                    const char* strIp = getServiceIp(token);
                    EV << "LARRY ~~~ " << strIp <<"\n";
                    if(strIp){
                        IPv4Service *entry = new IPv4Service();
                        entry->setServiceName(const_cast<char*>(token.c_str()));
                        //entry->setServiceId(1);
                        IPv4Address sIpv4(strIp);
                        entry->setServiceIp(sIpv4);
                        addService(entry);
                    }
                }

            }else
                EV <<"KHAC NHAU";
        }
    }
}

const char* IPv4ServiceTable::getServiceIp(std::string serviceName)
{
    serviceList = par("serviceList");
    cXMLElementList serviceDefineElements = serviceList->getChildrenByTagName("edge-service");
    for (auto & serviceDefineElement : serviceDefineElements) {
        const char *service = serviceDefineElement->getAttribute("service");
        const char *strIp = serviceDefineElement->getAttribute("ip");

        if(strcmp(serviceName.c_str(), service) == 0){
            return strIp;
        }
    }
    return NULL;
}

void IPv4ServiceTable::handleMessage(cMessage *msg)
{
    throw cRuntimeError("This module doesn't process messages");
}

void IPv4ServiceTable::addService(void *entry)
{
    IPv4Service *iS = (IPv4Service *) entry;
    //if not exist in Service Table, then add this entry
    if(isServiceCached(iS->getServiceIp()) == false){
        services.push_back(iS);
        iS->setServiceTable(this);
    }
}

void IPv4ServiceTable::deleteService(int index)
{
    IPv4Service *is = services.at(index);
    delete is;
    services.erase(services.begin() + index);
}

bool IPv4ServiceTable::isServiceCached(IPv4Address serviceDest)
{
    EV << "LARRY ~~~ serviceDest = " << serviceDest << "\n";
    //Check if service is cached in service Table or not
    for (std::vector<IPv4Service *>::iterator it = services.begin(); it != services.end(); ++it) {
        IPv4Service *service = *it;
        EV << "LARRY ~~~ service->getServiceIp() = " << service->getServiceIp() << "\n";
        if(service->getServiceIp().getInt() == serviceDest.getInt())
        {
            EV << "Exist Service !!!!! \n";
            return true;
        }
    }
    EV << "Service is not EXIST !!!!! \n";
    return false;
}

void IPv4ServiceTable::printServiceList()
{
    for (std::vector<IPv4Service *>::iterator it = services.begin(); it != services.end(); ++it) {
        IPv4Service *service = *it;
        EV << "LARRY ~~~ [IPv4ServiceTable] serviceName = " << service->getServiceName() <<" *** serviceIp = " << service->getServiceIp()<< "\n";
    }
}

int IPv4ServiceTable::getNumberOfService()
{
    return services.size();
}

int IPv4ServiceTable::getServiceSize(int index)
{
    if((index < services.size()) && (index >= 0))
        return services[index]->getSize();
    else
        return 0;
}

int IPv4ServiceTable::getServiceCacheSize(int index)
{
    if((index < services.size()) && (index >= 0))
        return services[index]->getCacheSize();
    else
        return 0;
}

int IPv4ServiceTable::getServiceMips(int index)
{
    if((index < services.size()) && (index >= 0))
        return services[index]->getMips();
    else
        return 0;
}

simtime_t IPv4ServiceTable::getLastRequestSecond(int index)
{
    if((index < services.size()) && (index >= 0))
        return services[index]->getLastRequestSecond();
    else
        return 0;
}

void IPv4ServiceTable::setServiceSize(int index, int size)
{
    if((index < services.size()) && (index >= 0))
        services[index]->setSize(size);
}

void IPv4ServiceTable::setServiceCacheSize(int index, int cacheSize)
{
    if((index < services.size()) && (index >= 0))
        services[index]->setCacheSize(cacheSize);
}

void IPv4ServiceTable::setServiceMips(int index, int mips)
{
    if((index < services.size()) && (index >= 0))
        services[index]->setMips(mips);
}

void IPv4ServiceTable::setLastRequestSecond(int index, simtime_t timeAt)
{
    if((index < services.size()) && (index >= 0))
        services[index]->setLastRequestSecond(timeAt);
}

int IPv4ServiceTable::getServiceIndex(IPv4Address serviceIp)
{
    EV << "LARRY ~~~ serviceIp = " << serviceIp << "\n";
    int size = services.size();
    //Check if service is cached in service Table or not
    for (int i = 0; i < size; i++) {
        if(services[i]->getServiceIp().getInt() == serviceIp.getInt())
        {
            return i;
        }
    }
    EV << "[getServiceIndex] Service is not EXIST !!!!! \n";
    return -1;
}

IPv4Address IPv4ServiceTable::getServiceAddress(int index)
{
    if((index < services.size()) && (index >= 0))
        return services[index]->getServiceIp();
    else{
        IPv4Address zero_address = IPv4Address();
        return zero_address;
    }
}

} // namespace inet

