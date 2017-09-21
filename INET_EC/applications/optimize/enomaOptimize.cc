/* Created by Larry */

#include "inet/applications/optimize/enomaOptimize.h"

namespace inet {

void enomaOptimize::doOptimize()
{
    EV << "LARRY ~~~ do Optimize heree !!!!!!!!! \n";

    int size = opt_ues.size();
    for (int i = 0; i < size; i++) {
        //Find Edge node near UE
        char* edge = getEdgeFromUe(opt_ues[i].node);
        //deployEdgeService(edge, opt_ues[i].child[0]);
    }
}

char* enomaOptimize::getEdgeFromUe(const char* ueIp)
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
} // namespace inet
