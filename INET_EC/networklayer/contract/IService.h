/* Created by LARRY */

#ifndef __INET_ISERVICE_H
#define __INET_ISERVICE_H

#include "inet/common/INETDefs.h"

namespace inet {

class IServiceTable;

class INET_API IService
{
  public:
    char * name;
    int id;
    IPv4Address serviceIpv4;


    virtual ~IService() {}
    IService() {}
    virtual int getServiceId(){
        return this->id;
    }
    virtual char* getServiceName(){
        return this->name;
    }

    virtual IPv4Address& getServiceIp(){
        return this->serviceIpv4;
    }

};

} // namespace inet

#endif // ifndef __INET_ISERVICE_H

