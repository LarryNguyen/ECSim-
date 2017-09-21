/* Created by Larry */
#ifndef __INET_IIPV4SERVICETABLE_H
#define __INET_IIPV4SERVICETABLE_H

#include <vector>

#include "inet/common/INETDefs.h"

#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include "inet/networklayer/contract/IServiceTable.h"

namespace inet {


class INET_API IIPv4ServiceTable : public IServiceTable
{
  public:
    virtual ~IIPv4ServiceTable() {};

};

} // namespace inet

#endif // ifndef __INET_IIPV4SERVICETABLE_H

