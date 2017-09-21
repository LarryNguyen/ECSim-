//Create by LARRY

namespace inet;

//
// Generic application packet
//
packet EnomaPackage
{
    //SP_REQUEST = 1, ENOMA_REQUEST = 2, EDGE_UPDATE_ST=3
    int msgType;
    //IP of UE
    string ueIp;
    //Service name
    string sp;
    //size of service container
    int size;
    //size of service Cache
    int cacheSize;
    //mips
    int mips;
    //List of Edge Service should be install in Edge Node
    string listEdgeService;    
    string nodeName; //eg. Egde1, Edge2...
}
