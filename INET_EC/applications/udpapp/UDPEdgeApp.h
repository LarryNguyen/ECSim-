/* Created by Larry */

#ifndef __INET_UDPEDGEAPP_H
#define __INET_UDPEDGEAPP_H

#include <vector>

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/transportlayer/contract/udp/UDPSocket.h"
#include "inet/networklayer/ipv4/IIPv4ServiceTable.h"

namespace inet {

/**
 * UDP application. See NED for more info.
 */
class INET_API UDPEdgeApp : public ApplicationBase
{
  protected:
    enum SelfMsgKinds { START = 1, SEND, STOP, UPDATE_ST };

    // parameters
    IIPv4ServiceTable *st;
    std::vector<L3Address> destAddresses;
    std::vector<L3Address> enomaAddresses;
    int localPort = -1, destPort = -1;
    int enomaPort = -1;
    simtime_t startTime;
    simtime_t stopTime;
    const char *packetName = nullptr;
    int isEnoma = -1;
    int isEdgeNode = -1;
    int isSP = -1;
    int mips = 0;
    int size = 0;
    int cacheSize = 0;
    char *removedServiceList = new char[4096];
    // state
    UDPSocket socket;
    cMessage *selfMsg = nullptr;

    // statistics
    int numSent = 0;
    int numReceived = 0;

    simtime_t disable_service_interval;

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
    virtual L3Address getEnomaAddr();
    virtual void sendPacket();
    virtual void processPacket(cPacket *msg);
    virtual void setSocketOptions();

    virtual void processStart();
    virtual void processSend();
    virtual void processStop();
    virtual void processUpdateSt();

    virtual bool handleNodeStart(IDoneCallback *doneCallback) override;
    virtual bool handleNodeShutdown(IDoneCallback *doneCallback) override;
    virtual void handleNodeCrash() override;

  public:
    UDPEdgeApp() {}
    ~UDPEdgeApp();
};

} // namespace inet

#endif // ifndef __INET_UDPEDGEAPP_H

