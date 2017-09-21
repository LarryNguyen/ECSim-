//
// Generated file, do not edit! Created by nedtool 5.1 from inet/networklayer/ted/LinkStatePacket.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_LINKSTATEPACKET_M_H
#define __INET_LINKSTATEPACKET_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif

// cplusplus {{
#include "inet/networklayer/ted/TED_m.h"
// }}


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/ted/LinkStatePacket.msg:33</tt> by nedtool.
 * <pre>
 * //
 * // Packet for disseminating link state information (~TELinkStateInfo[]) by the
 * // ~LinkStateRouting module which implements a minimalistic link state routing
 * // protocol.
 * //
 * packet LinkStateMsg
 * {
 *     TELinkStateInfo linkInfo[];
 * 
 *     bool request = false; // if true, receiver is expected to send back its own link state database to the sender --FIXME really needed?
 *         // bool ack = false; -- apparently unused, removed -- TODO check with Vojta
 * 
 *     int command = LINK_STATE_MESSAGE; // FIXME maybe do without this...
 * }
 * </pre>
 */
class INET_API LinkStateMsg : public ::omnetpp::cPacket
{
  protected:
    TELinkStateInfo *linkInfo; // array ptr
    unsigned int linkInfo_arraysize;
    bool request;
    int command;

  private:
    void copy(const LinkStateMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const LinkStateMsg&);

  public:
    LinkStateMsg(const char *name=nullptr, short kind=0);
    LinkStateMsg(const LinkStateMsg& other);
    virtual ~LinkStateMsg();
    LinkStateMsg& operator=(const LinkStateMsg& other);
    virtual LinkStateMsg *dup() const override {return new LinkStateMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setLinkInfoArraySize(unsigned int size);
    virtual unsigned int getLinkInfoArraySize() const;
    virtual TELinkStateInfo& getLinkInfo(unsigned int k);
    virtual const TELinkStateInfo& getLinkInfo(unsigned int k) const {return const_cast<LinkStateMsg*>(this)->getLinkInfo(k);}
    virtual void setLinkInfo(unsigned int k, const TELinkStateInfo& linkInfo);
    virtual bool getRequest() const;
    virtual void setRequest(bool request);
    virtual int getCommand() const;
    virtual void setCommand(int command);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LinkStateMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LinkStateMsg& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_LINKSTATEPACKET_M_H

