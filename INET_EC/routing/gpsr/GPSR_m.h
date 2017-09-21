//
// Generated file, do not edit! Created by nedtool 5.1 from inet/routing/gpsr/GPSR.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_GPSR_M_H
#define __INET_GPSR_M_H

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
#include "inet/common/geometry/common/Coord.h"
#include "inet/common/TLVOption.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/routing/gpsr/GPSRDefs.h"
// }}


namespace inet {

/**
 * Class generated from <tt>inet/routing/gpsr/GPSR.msg:41</tt> by nedtool.
 * <pre>
 * //
 * // The GPSR beacon packet is sent periodically by all GPSR routers to notify
 * // the neighbors about the router's address and position.
 * //
 * packet GPSRBeacon
 * {
 *     L3Address address;
 *     Coord position;
 * }
 * </pre>
 */
class INET_API GPSRBeacon : public ::omnetpp::cPacket
{
  protected:
    L3Address address;
    Coord position;

  private:
    void copy(const GPSRBeacon& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GPSRBeacon&);

  public:
    GPSRBeacon(const char *name=nullptr, short kind=0);
    GPSRBeacon(const GPSRBeacon& other);
    virtual ~GPSRBeacon();
    GPSRBeacon& operator=(const GPSRBeacon& other);
    virtual GPSRBeacon *dup() const override {return new GPSRBeacon(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual L3Address& getAddress();
    virtual const L3Address& getAddress() const {return const_cast<GPSRBeacon*>(this)->getAddress();}
    virtual void setAddress(const L3Address& address);
    virtual Coord& getPosition();
    virtual const Coord& getPosition() const {return const_cast<GPSRBeacon*>(this)->getPosition();}
    virtual void setPosition(const Coord& position);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GPSRBeacon& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GPSRBeacon& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/gpsr/GPSR.msg:52</tt> by nedtool.
 * <pre>
 * //
 * // The GPSROption is used to add extra routing information for network datagrams.
 * //
 * // For more information, see the GPSR paper
 * // http://www.eecs.harvard.edu/~htk/publication/2000-mobi-karp-kung.pdf
 * //
 * class GPSROption extends TLVOptionBase
 * {
 *     GPSRForwardingMode routingMode = (GPSRForwardingMode)-1;
 *     Coord destinationPosition;               // D
 *     Coord perimeterRoutingStartPosition;     // Lp
 *     Coord perimeterRoutingForwardPosition;   // Lf
 *     L3Address currentFaceFirstSenderAddress;   // e0
 *     L3Address currentFaceFirstReceiverAddress; // e0
 *     L3Address senderAddress; // TODO: this field is not strictly needed by GPSR (should be eliminated)
 * }
 * </pre>
 */
class INET_API GPSROption : public ::inet::TLVOptionBase
{
  protected:
    GPSRForwardingMode routingMode;
    Coord destinationPosition;
    Coord perimeterRoutingStartPosition;
    Coord perimeterRoutingForwardPosition;
    L3Address currentFaceFirstSenderAddress;
    L3Address currentFaceFirstReceiverAddress;
    L3Address senderAddress;

  private:
    void copy(const GPSROption& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GPSROption&);

  public:
    GPSROption();
    GPSROption(const GPSROption& other);
    virtual ~GPSROption();
    GPSROption& operator=(const GPSROption& other);
    virtual GPSROption *dup() const override {return new GPSROption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual GPSRForwardingMode& getRoutingMode();
    virtual const GPSRForwardingMode& getRoutingMode() const {return const_cast<GPSROption*>(this)->getRoutingMode();}
    virtual void setRoutingMode(const GPSRForwardingMode& routingMode);
    virtual Coord& getDestinationPosition();
    virtual const Coord& getDestinationPosition() const {return const_cast<GPSROption*>(this)->getDestinationPosition();}
    virtual void setDestinationPosition(const Coord& destinationPosition);
    virtual Coord& getPerimeterRoutingStartPosition();
    virtual const Coord& getPerimeterRoutingStartPosition() const {return const_cast<GPSROption*>(this)->getPerimeterRoutingStartPosition();}
    virtual void setPerimeterRoutingStartPosition(const Coord& perimeterRoutingStartPosition);
    virtual Coord& getPerimeterRoutingForwardPosition();
    virtual const Coord& getPerimeterRoutingForwardPosition() const {return const_cast<GPSROption*>(this)->getPerimeterRoutingForwardPosition();}
    virtual void setPerimeterRoutingForwardPosition(const Coord& perimeterRoutingForwardPosition);
    virtual L3Address& getCurrentFaceFirstSenderAddress();
    virtual const L3Address& getCurrentFaceFirstSenderAddress() const {return const_cast<GPSROption*>(this)->getCurrentFaceFirstSenderAddress();}
    virtual void setCurrentFaceFirstSenderAddress(const L3Address& currentFaceFirstSenderAddress);
    virtual L3Address& getCurrentFaceFirstReceiverAddress();
    virtual const L3Address& getCurrentFaceFirstReceiverAddress() const {return const_cast<GPSROption*>(this)->getCurrentFaceFirstReceiverAddress();}
    virtual void setCurrentFaceFirstReceiverAddress(const L3Address& currentFaceFirstReceiverAddress);
    virtual L3Address& getSenderAddress();
    virtual const L3Address& getSenderAddress() const {return const_cast<GPSROption*>(this)->getSenderAddress();}
    virtual void setSenderAddress(const L3Address& senderAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GPSROption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GPSROption& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_GPSR_M_H

