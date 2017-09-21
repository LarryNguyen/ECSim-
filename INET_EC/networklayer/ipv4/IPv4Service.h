/* Create by LARRY */

#ifndef __INET_IPV4SERVICE_H
#define __INET_IPV4SERVICE_H

#include "inet/common/INETDefs.h"
#include "inet/networklayer/contract/IService.h"
#include "inet/networklayer/ipv4/IIPv4ServiceTable.h"
#include "inet/networklayer/common/L3Address.h"

namespace inet {
class IIPv4ServiceTable;
class INET_API IPv4Service : public cObject, public IService {


private:
    IIPv4ServiceTable *st;    ///< the routing table in which this route is inserted, or nullptr
    char* name;
    int id;
    IPv4Address serviceIpv4;
    int size;
    int cacheSize;
    int mips;
    simtime_t last_request_second;
public:
    IPv4Service() : st(nullptr), name(nullptr), id(0) {}
    //IPv4Service() : name(nullptr), id(0) {}
    virtual ~IPv4Service() {}
    char * getServiceName() {return this->name;}
    int getServiceId() {return this->id;}
    IPv4Address& getServiceIp() {return this->serviceIpv4;}
    int getSize() {return this->size;}
    int getCacheSize() {return this->cacheSize;}
    int getMips() {return this->mips;}
    simtime_t getLastRequestSecond() {return this->last_request_second;}

    void setServiceName(char* n) {this->name = n;}
    void setServiceId(int i) {this->id = i;}
    void setServiceIp(IPv4Address ip) {this->serviceIpv4 = ip;}
    void setSize(int size) {this->size = size;}
    void setCacheSize(int cacheSize) {this->cacheSize = cacheSize;}
    void setMips(int mips) {this->mips = mips;}
    void setLastRequestSecond(simtime_t timeAt) {this->last_request_second = timeAt;}

    /** To be called by the services table when this service is added or removed from it */
    virtual void setServiceTable(IIPv4ServiceTable *st) { this->st = st; }
    IIPv4ServiceTable *getServiceTable() const { return this->st; }

};

} // namespace inet

#endif    // __INET_IPV4SERVICE_H

