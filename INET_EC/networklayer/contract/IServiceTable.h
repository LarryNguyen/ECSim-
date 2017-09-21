/* Created by LARRY */

#ifndef __INET_ISERVICETABLE_H
#define __INET_ISERVICETABLE_H

#include "inet/common/INETDefs.h"
#include "inet/networkLayer/contract/IService.h"

namespace inet {

/**
 * A C++ interface to abstract the functionality of a routing table, regardless of address type.
 */
class INET_API IServiceTable
{
//private:
//    int size;
//    int cacheSize;
//    int mips;
  public:
    virtual ~IServiceTable() {};

    /** @name Miscellaneous functions */
    //@{
    //TODO:
    // Add more functions for service Table (add/delete)
    /**
     * Adds a route to the routing table. Routes are allowed to be modified
     * while in the routing table. (There is a notification mechanism that
     * allows routing table internals to be updated on a routing entry change.)
     */
    virtual void addService(void *entry) = 0;

    /**
     * Deletes the given route from the routing table.
     * Returns true if the route was deleted, and false if it was
     * not in the routing table.
     */
    virtual void deleteService(int index) = 0;

    virtual bool isServiceCached(IPv4Address serviceDest) = 0;

    virtual void printServiceList() = 0;

    virtual int getNumberOfService() = 0;

    virtual int getServiceIndex(IPv4Address serviceIp) = 0;

    virtual int getServiceSize(int index) = 0;
    virtual int getServiceCacheSize(int index) = 0;
    virtual int getServiceMips(int index) = 0;
    virtual simtime_t getLastRequestSecond(int index) = 0;
    virtual IPv4Address getServiceAddress(int index) = 0;

    virtual void setServiceSize(int index, int size) = 0;
    virtual void setServiceCacheSize(int index, int cacheSize) = 0;
    virtual void setServiceMips(int index, int mips) = 0;
    virtual void setLastRequestSecond(int index, simtime_t timeAt) = 0;
};

} // namespace inet

#endif // ifndef __INET_ISERVICETABLE_H

