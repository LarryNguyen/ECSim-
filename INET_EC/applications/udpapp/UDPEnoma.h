/* Created by Larry */

#ifndef __INET_UDPENOMA_H
#define __INET_UDPENOMA_H

#include <vector>

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/transportlayer/contract/udp/UDPSocket.h"

namespace inet {
#define MAX 10
/**
 * UDP application. See NED for more info.
 */
class INET_API UDPEnoma : public ApplicationBase
{
  protected:
    enum SelfMsgKinds { START = 1, SEND, STOP, OPTIMIZE };

    // parameters
    std::vector<L3Address> destAddresses;
    int localPort = -1, destPort = -1;
    simtime_t startTime;
    simtime_t stopTime;
    const char *packetName = nullptr;
    int isEnoma = -1;
    int isEdgeNode = -1;
    cXMLElement *topology = nullptr;

    // Use for save table network topology

    struct stable
    {
       char node[256];
       char child[256][MAX];
    };

    struct serviceInfo
    {
        char name[256];
        int size;
        int cacheSize;
        int mips;
    };

    std::vector<stable> topo_edges;
    std::vector<stable> topo_rgs;
    std::vector<stable> topo_cores;

    std::vector<stable> service_nodes;
    //std::vector<stable> service_rgs;
    //std::vector<stable> service_cores;

    std::vector<stable> opt_edges;
    std::vector<stable> opt_rgs;
    std::vector<stable> opt_cores;
    std::vector<stable> opt_ues;

    std::vector<serviceInfo> serviceInfoTable;
    // state
    UDPSocket socket;
    cMessage *selfMsg = nullptr;

    // statistics
    int numSent = 0;
    int numReceived = 0;

    static simsignal_t sentPkSignal;
    static simsignal_t rcvdPkSignal;

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    // chooses random destination address
    virtual L3Address chooseDestAddr();
    virtual void sendPacket();
    virtual void processPacket(cPacket *msg);
    virtual void setSocketOptions();

    virtual void processStart();
    virtual void processSend();
    virtual void processStop();
    virtual void processTopology();
    virtual void processOptimize();

    virtual char* getEdgeFromUe(const char* ueIp);
    virtual char* getRgFromEdge(const char* edge);
    virtual char* getCoreFromRg(const char* rg);

    virtual bool handleNodeStart(IDoneCallback *doneCallback) override;
    virtual bool handleNodeShutdown(IDoneCallback *doneCallback) override;
    virtual void handleNodeCrash() override;

    virtual void deployEdgeService(const char* edge, const char* service);
    virtual int getUeIndexInRequestServiceTable(const char *ue);
    virtual void updateUeServiceInfo(cPacket *pk);
    virtual void runOptimizeTest();
    virtual bool isExistInServiceInfoTable(const char *serviceName);
    virtual int getNodeIndexFromServiceNodeTable(const char *node);
  public:
    UDPEnoma() {}
    ~UDPEnoma();
};

} // namespace inet

#endif // ifndef __INET_UDPENOMA_H

