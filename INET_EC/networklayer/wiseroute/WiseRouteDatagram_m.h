//
// Generated file, do not edit! Created by nedtool 5.1 from inet/networklayer/wiseroute/WiseRouteDatagram.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_WISEROUTEDATAGRAM_M_H
#define __INET_WISEROUTEDATAGRAM_M_H

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
   #include "inet/networklayer/base/NetworkDatagramBase_m.h"
// }}


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/wiseroute/WiseRouteDatagram.msg:28</tt> by nedtool.
 * <pre>
 * packet WiseRouteDatagram extends NetworkDatagramBase
 * {
 *     \@customize(true);
 * 
 *     unsigned long seqNum = 0;
 *     int isFlood;
 *     int nbHops;
 *     int transportProtocol = -1;
 *     L3Address finalDestAddr;
 *     L3Address initialSrcAddr;
 * }
 * </pre>
 *
 * WiseRouteDatagram_Base is only useful if it gets subclassed, and WiseRouteDatagram is derived from it.
 * The minimum code to be written for WiseRouteDatagram is the following:
 *
 * <pre>
 * class INET_API WiseRouteDatagram : public WiseRouteDatagram_Base
 * {
 *   private:
 *     void copy(const WiseRouteDatagram& other) { ... }

 *   public:
 *     WiseRouteDatagram(const char *name=nullptr, short kind=0) : WiseRouteDatagram_Base(name,kind) {}
 *     WiseRouteDatagram(const WiseRouteDatagram& other) : WiseRouteDatagram_Base(other) {copy(other);}
 *     WiseRouteDatagram& operator=(const WiseRouteDatagram& other) {if (this==&other) return *this; WiseRouteDatagram_Base::operator=(other); copy(other); return *this;}
 *     virtual WiseRouteDatagram *dup() const override {return new WiseRouteDatagram(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from WiseRouteDatagram_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(WiseRouteDatagram)
 * </pre>
 */
class INET_API WiseRouteDatagram_Base : public ::inet::NetworkDatagramBase
{
  protected:
    unsigned long seqNum;
    int isFlood;
    int nbHops;
    int transportProtocol;
    L3Address finalDestAddr;
    L3Address initialSrcAddr;

  private:
    void copy(const WiseRouteDatagram_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const WiseRouteDatagram_Base&);
    // make constructors protected to avoid instantiation
    WiseRouteDatagram_Base(const char *name=nullptr, short kind=0);
    WiseRouteDatagram_Base(const WiseRouteDatagram_Base& other);
    // make assignment operator protected to force the user override it
    WiseRouteDatagram_Base& operator=(const WiseRouteDatagram_Base& other);

  public:
    virtual ~WiseRouteDatagram_Base();
    virtual WiseRouteDatagram_Base *dup() const override {throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class WiseRouteDatagram");}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned long getSeqNum() const;
    virtual void setSeqNum(unsigned long seqNum);
    virtual int getIsFlood() const;
    virtual void setIsFlood(int isFlood);
    virtual int getNbHops() const;
    virtual void setNbHops(int nbHops);
    virtual int getTransportProtocol() const;
    virtual void setTransportProtocol(int transportProtocol);
    virtual L3Address& getFinalDestAddr();
    virtual const L3Address& getFinalDestAddr() const {return const_cast<WiseRouteDatagram_Base*>(this)->getFinalDestAddr();}
    virtual void setFinalDestAddr(const L3Address& finalDestAddr);
    virtual L3Address& getInitialSrcAddr();
    virtual const L3Address& getInitialSrcAddr() const {return const_cast<WiseRouteDatagram_Base*>(this)->getInitialSrcAddr();}
    virtual void setInitialSrcAddr(const L3Address& initialSrcAddr);
};

} // namespace inet

#endif // ifndef __INET_WISEROUTEDATAGRAM_M_H

