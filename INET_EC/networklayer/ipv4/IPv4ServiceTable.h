/* Created by LARRY */

#ifndef __INET_IPV4SERVICETABLE_H
#define __INET_IPV4SERVICETABLE_H

#include <vector>

#include "inet/common/INETDefs.h"

#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/networklayer/contract/IServiceTable.h"
#include "inet/networklayer/ipv4/IPv4Service.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/ipv4/IIPv4ServiceTable.h"

namespace inet {

class INET_API IPv4ServiceTable : public cSimpleModule, public IIPv4ServiceTable
{
  public:

    virtual void initialize(int stage) override;

    virtual void handleMessage(cMessage *) override;

    virtual void addService(void *entry);
    virtual void deleteService(int index);
    virtual bool isServiceCached(IPv4Address serviceDest);
    virtual void printServiceList();
    virtual int getNumberOfService();
    virtual int getServiceSize(int index);
    virtual int getServiceCacheSize(int index);
    virtual int getServiceMips(int index);
    virtual int getServiceIndex(IPv4Address serviceIp);
    virtual IPv4Address getServiceAddress(int index);

    virtual void setServiceSize(int index, int size);
    virtual void setServiceCacheSize(int index, int cacheSize);
    virtual void setServiceMips(int index, int mips);
    virtual simtime_t getLastRequestSecond(int index);
    virtual void setLastRequestSecond(int index, simtime_t timeAt);

    IPv4ServiceTable() {}
    virtual ~IPv4ServiceTable();

  private:
    cXMLElement *configuration = nullptr;
    cXMLElement *serviceList = nullptr;
    typedef std::vector<IPv4Service *> ServiceVector;
    ServiceVector services;    // services vector of one node/host
    const char* getServiceIp(std::string serviceName);

};

} // namespace inet

#endif // ifndef __INET_IPV4SERVICETABLE_H

