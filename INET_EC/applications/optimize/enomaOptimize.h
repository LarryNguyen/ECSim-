/* Created by Larry */

#ifndef __INET_ENOMAOPTIMIZE_H
#define __INET_ENOMAOPTIMIZE_H

#include <vector>

#include "inet/common/INETDefs.h"

namespace inet {
#define MAX 10
class INET_API enomaOptimize
{
    public:
        struct stable
            {
               char node[256];
               char child[256][MAX];
            };

        std::vector<stable> topo_edges;
        std::vector<stable> topo_rgs;
        std::vector<stable> topo_cores;

        std::vector<stable> opt_edges;
        std::vector<stable> opt_rgs;
        std::vector<stable> opt_cores;
        std::vector<stable> opt_ues;
  public:
    enomaOptimize() {}
    ~enomaOptimize() {}

    virtual void doOptimize();
    virtual char* getEdgeFromUe(const char* ueIp);
};

} // namespace inet

#endif // ifndef __INET_ENOMAOPTIMIZE_H

