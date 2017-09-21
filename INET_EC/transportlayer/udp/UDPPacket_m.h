//
// Generated file, do not edit! Created by nedtool 5.1 from inet/transportlayer/udp/UDPPacket.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_UDPPACKET_M_H
#define __INET_UDPPACKET_M_H

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
#include "inet/common/INETDefs.h"
// }}


namespace inet {

/**
 * Enum generated from <tt>inet/transportlayer/udp/UDPPacket.msg:26</tt> by nedtool.
 * <pre>
 * enum UdpConstants
 * {
 * 
 *     UDP_HEADER_BYTES = 8;
 * }
 * </pre>
 */
enum UdpConstants {
    UDP_HEADER_BYTES = 8
};

/**
 * Class generated from <tt>inet/transportlayer/udp/UDPPacket.msg:33</tt> by nedtool.
 * <pre>
 * //
 * // Represents an UDP packet, to be used with the ~UDP module.
 * //
 * packet UDPPacket
 * {
 *     \@customize(true);
 *     unsigned short srcPort;
 *     unsigned short destPort;
 *     byteLength = UDP_HEADER_BYTES;
 *     int totalLengthField = -1;   // -1 means: getTotalLengthField() uses getByteLength()
 * }
 * </pre>
 *
 * UDPPacket_Base is only useful if it gets subclassed, and UDPPacket is derived from it.
 * The minimum code to be written for UDPPacket is the following:
 *
 * <pre>
 * class INET_API UDPPacket : public UDPPacket_Base
 * {
 *   private:
 *     void copy(const UDPPacket& other) { ... }

 *   public:
 *     UDPPacket(const char *name=nullptr, short kind=0) : UDPPacket_Base(name,kind) {}
 *     UDPPacket(const UDPPacket& other) : UDPPacket_Base(other) {copy(other);}
 *     UDPPacket& operator=(const UDPPacket& other) {if (this==&other) return *this; UDPPacket_Base::operator=(other); copy(other); return *this;}
 *     virtual UDPPacket *dup() const override {return new UDPPacket(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from UDPPacket_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(UDPPacket)
 * </pre>
 */
class INET_API UDPPacket_Base : public ::omnetpp::cPacket
{
  protected:
    unsigned short srcPort;
    unsigned short destPort;
    int totalLengthField;

  private:
    void copy(const UDPPacket_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const UDPPacket_Base&);
    // make constructors protected to avoid instantiation
    UDPPacket_Base(const char *name=nullptr, short kind=0);
    UDPPacket_Base(const UDPPacket_Base& other);
    // make assignment operator protected to force the user override it
    UDPPacket_Base& operator=(const UDPPacket_Base& other);

  public:
    virtual ~UDPPacket_Base();
    virtual UDPPacket_Base *dup() const override {throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class UDPPacket");}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned short getSrcPort() const;
    virtual void setSrcPort(unsigned short srcPort);
    virtual unsigned short getDestPort() const;
    virtual void setDestPort(unsigned short destPort);
    virtual int getTotalLengthField() const;
    virtual void setTotalLengthField(int totalLengthField);
};

} // namespace inet

#endif // ifndef __INET_UDPPACKET_M_H
