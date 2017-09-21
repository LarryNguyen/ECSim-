//
// Generated file, do not edit! Created by nedtool 5.1 from inet/networklayer/rsvp_te/RSVPPacket.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_RSVPPACKET_M_H
#define __INET_RSVPPACKET_M_H

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
#include "inet/networklayer/rsvp_te/IntServ_m.h"

#define PATH_MESSAGE   1
#define RESV_MESSAGE   2
#define PTEAR_MESSAGE  3
#define RTEAR_MESSAGE  4
#define PERROR_MESSAGE 5
#define RERROR_MESSAGE 6
#define HELLO_MESSAGE   7
// }}


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/rsvp_te/RSVPPacket.msg:57</tt> by nedtool.
 * <pre>
 * //
 * // RSVP message common part
 * //
 * packet RSVPMessage
 * {
 *     int rsvpKind;
 * }
 * </pre>
 */
class INET_API RSVPMessage : public ::omnetpp::cPacket
{
  protected:
    int rsvpKind;

  private:
    void copy(const RSVPMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RSVPMessage&);

  public:
    RSVPMessage(const char *name=nullptr, short kind=0);
    RSVPMessage(const RSVPMessage& other);
    virtual ~RSVPMessage();
    RSVPMessage& operator=(const RSVPMessage& other);
    virtual RSVPMessage *dup() const override {return new RSVPMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getRsvpKind() const;
    virtual void setRsvpKind(int rsvpKind);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RSVPMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RSVPMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/rsvp_te/RSVPPacket.msg:65</tt> by nedtool.
 * <pre>
 * //
 * // FIXME missing documentation
 * //
 * packet RSVPPacket extends RSVPMessage
 * {
 *     \@customize(true);
 *     SessionObj_t session;
 *     bool checksumValid = true;
 * }
 * </pre>
 *
 * RSVPPacket_Base is only useful if it gets subclassed, and RSVPPacket is derived from it.
 * The minimum code to be written for RSVPPacket is the following:
 *
 * <pre>
 * class INET_API RSVPPacket : public RSVPPacket_Base
 * {
 *   private:
 *     void copy(const RSVPPacket& other) { ... }

 *   public:
 *     RSVPPacket(const char *name=nullptr, short kind=0) : RSVPPacket_Base(name,kind) {}
 *     RSVPPacket(const RSVPPacket& other) : RSVPPacket_Base(other) {copy(other);}
 *     RSVPPacket& operator=(const RSVPPacket& other) {if (this==&other) return *this; RSVPPacket_Base::operator=(other); copy(other); return *this;}
 *     virtual RSVPPacket *dup() const override {return new RSVPPacket(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from RSVPPacket_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(RSVPPacket)
 * </pre>
 */
class INET_API RSVPPacket_Base : public ::inet::RSVPMessage
{
  protected:
    SessionObj_t session;
    bool checksumValid;

  private:
    void copy(const RSVPPacket_Base& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RSVPPacket_Base&);
    // make constructors protected to avoid instantiation
    RSVPPacket_Base(const char *name=nullptr, short kind=0);
    RSVPPacket_Base(const RSVPPacket_Base& other);
    // make assignment operator protected to force the user override it
    RSVPPacket_Base& operator=(const RSVPPacket_Base& other);

  public:
    virtual ~RSVPPacket_Base();
    virtual RSVPPacket_Base *dup() const override {throw omnetpp::cRuntimeError("You forgot to manually add a dup() function to class RSVPPacket");}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual SessionObj_t& getSession();
    virtual const SessionObj_t& getSession() const {return const_cast<RSVPPacket_Base*>(this)->getSession();}
    virtual void setSession(const SessionObj_t& session);
    virtual bool getChecksumValid() const;
    virtual void setChecksumValid(bool checksumValid);
};

} // namespace inet

#endif // ifndef __INET_RSVPPACKET_M_H

