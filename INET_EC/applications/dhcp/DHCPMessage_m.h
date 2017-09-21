//
// Generated file, do not edit! Created by nedtool 5.1 from inet/applications/dhcp/DHCPMessage.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET_DHCPMESSAGE_M_H
#define __INET_DHCPMESSAGE_M_H

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
#include "inet/linklayer/common/MACAddress.h"
#include "inet/networklayer/contract/ipv4/IPv4Address.h"
// }}


namespace inet {

/**
 * Enum generated from <tt>inet/applications/dhcp/DHCPMessage.msg:31</tt> by nedtool.
 * <pre>
 * enum DHCPOpcode
 * {
 * 
 *     BOOTREQUEST = 1;
 *     BOOTREPLY = 2;
 * }
 * </pre>
 */
enum DHCPOpcode {
    BOOTREQUEST = 1,
    BOOTREPLY = 2
};

/**
 * Enum generated from <tt>inet/applications/dhcp/DHCPMessage.msg:37</tt> by nedtool.
 * <pre>
 * enum DHCPMessageType
 * {
 * 
 *     DHCPDISCOVER = 1;
 *     DHCPOFFER = 2;
 *     DHCPREQUEST = 3;
 *     DHCPDECLINE = 4;
 *     DHCPACK = 5;
 *     DHCPNAK = 6;
 *     DHCPRELEASE = 7;
 *     DHCPINFORM = 8;
 * }
 * </pre>
 */
enum DHCPMessageType {
    DHCPDISCOVER = 1,
    DHCPOFFER = 2,
    DHCPREQUEST = 3,
    DHCPDECLINE = 4,
    DHCPACK = 5,
    DHCPNAK = 6,
    DHCPRELEASE = 7,
    DHCPINFORM = 8
};

/**
 * Enum generated from <tt>inet/applications/dhcp/DHCPMessage.msg:49</tt> by nedtool.
 * <pre>
 * enum DHCPOptionCode
 * {
 * 
 *     DHCP_MSG_TYPE = 53;
 *     CLIENT_ID = 61;
 *     HOSTNAME = 12;
 *     REQUESTED_IP = 50;
 *     PARAM_LIST = 55;
 *     SUBNET_MASK = 1;
 *     ROUTER = 3;
 *     DNS = 6;
 *     NTP_SRV = 42;
 *     RENEWAL_TIME = 58;
 *     REBIND_TIME = 59;
 *     LEASE_TIME = 51;
 *     SERVER_ID = 54;
 * }
 * </pre>
 */
enum DHCPOptionCode {
    DHCP_MSG_TYPE = 53,
    CLIENT_ID = 61,
    HOSTNAME = 12,
    REQUESTED_IP = 50,
    PARAM_LIST = 55,
    SUBNET_MASK = 1,
    ROUTER = 3,
    DNS = 6,
    NTP_SRV = 42,
    RENEWAL_TIME = 58,
    REBIND_TIME = 59,
    LEASE_TIME = 51,
    SERVER_ID = 54
};

/**
 * Class generated from <tt>inet/applications/dhcp/DHCPMessage.msg:74</tt> by nedtool.
 * <pre>
 * //
 * // Represents options in a DHCP message. In the DHCP protocol, options are
 * // added to the message as tagged data items. In the simulation, this DHCPOptions
 * // class statically holds the union of all options actually used by the DHCP
 * // protocol models. Options absent from a packet are represented by empty/unfilled
 * // DHCPOptions fields.
 * //
 * // \@see DHCPMessage, DHCPClient, DHCPServer
 * //
 * class DHCPOptions
 * {
 *     int messageType \@enum(DHCPMessageType); // to convey the type of the DHCP message
 *     string hostName; // name of the client
 *     int parameterRequestList[]; // used by a DHCP client to request values for specified configuration parameters
 *     MACAddress clientIdentifier; // used by DHCP clients to specify their unique identifier
 *     IPv4Address requestedIp; // used in a client request (DHCPDISCOVER) to allow the client to request that a particular IP address be assigned
 *     IPv4Address subnetMask; // client's subnet mask
 *     IPv4Address router[]; // IP addresses for routers on the client's subnet
 *     IPv4Address dns[]; // list of DNSs available to the client
 *     IPv4Address ntp[]; // list of IP addresses indicating NTP servers available to the client
 *     IPv4Address serverIdentifier; // client use this field as the destination address for any unicast DHCP messages to the server
 *     simtime_t renewalTime; // time interval (T1) from address assignment until the client transitions to the RENEWING state
 *     simtime_t rebindingTime; // time interval (T2) from address assignment until the client transitions to the REBINDING state
 *     simtime_t leaseTime; // request for lease time (client), offered lease time (server)
 * }
 * </pre>
 */
class INET_API DHCPOptions : public ::omnetpp::cObject
{
  protected:
    int messageType;
    ::omnetpp::opp_string hostName;
    int *parameterRequestList; // array ptr
    unsigned int parameterRequestList_arraysize;
    MACAddress clientIdentifier;
    IPv4Address requestedIp;
    IPv4Address subnetMask;
    IPv4Address *router; // array ptr
    unsigned int router_arraysize;
    IPv4Address *dns; // array ptr
    unsigned int dns_arraysize;
    IPv4Address *ntp; // array ptr
    unsigned int ntp_arraysize;
    IPv4Address serverIdentifier;
    ::omnetpp::simtime_t renewalTime;
    ::omnetpp::simtime_t rebindingTime;
    ::omnetpp::simtime_t leaseTime;

  private:
    void copy(const DHCPOptions& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DHCPOptions&);

  public:
    DHCPOptions();
    DHCPOptions(const DHCPOptions& other);
    virtual ~DHCPOptions();
    DHCPOptions& operator=(const DHCPOptions& other);
    virtual DHCPOptions *dup() const override {return new DHCPOptions(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getMessageType() const;
    virtual void setMessageType(int messageType);
    virtual const char * getHostName() const;
    virtual void setHostName(const char * hostName);
    virtual void setParameterRequestListArraySize(unsigned int size);
    virtual unsigned int getParameterRequestListArraySize() const;
    virtual int getParameterRequestList(unsigned int k) const;
    virtual void setParameterRequestList(unsigned int k, int parameterRequestList);
    virtual MACAddress& getClientIdentifier();
    virtual const MACAddress& getClientIdentifier() const {return const_cast<DHCPOptions*>(this)->getClientIdentifier();}
    virtual void setClientIdentifier(const MACAddress& clientIdentifier);
    virtual IPv4Address& getRequestedIp();
    virtual const IPv4Address& getRequestedIp() const {return const_cast<DHCPOptions*>(this)->getRequestedIp();}
    virtual void setRequestedIp(const IPv4Address& requestedIp);
    virtual IPv4Address& getSubnetMask();
    virtual const IPv4Address& getSubnetMask() const {return const_cast<DHCPOptions*>(this)->getSubnetMask();}
    virtual void setSubnetMask(const IPv4Address& subnetMask);
    virtual void setRouterArraySize(unsigned int size);
    virtual unsigned int getRouterArraySize() const;
    virtual IPv4Address& getRouter(unsigned int k);
    virtual const IPv4Address& getRouter(unsigned int k) const {return const_cast<DHCPOptions*>(this)->getRouter(k);}
    virtual void setRouter(unsigned int k, const IPv4Address& router);
    virtual void setDnsArraySize(unsigned int size);
    virtual unsigned int getDnsArraySize() const;
    virtual IPv4Address& getDns(unsigned int k);
    virtual const IPv4Address& getDns(unsigned int k) const {return const_cast<DHCPOptions*>(this)->getDns(k);}
    virtual void setDns(unsigned int k, const IPv4Address& dns);
    virtual void setNtpArraySize(unsigned int size);
    virtual unsigned int getNtpArraySize() const;
    virtual IPv4Address& getNtp(unsigned int k);
    virtual const IPv4Address& getNtp(unsigned int k) const {return const_cast<DHCPOptions*>(this)->getNtp(k);}
    virtual void setNtp(unsigned int k, const IPv4Address& ntp);
    virtual IPv4Address& getServerIdentifier();
    virtual const IPv4Address& getServerIdentifier() const {return const_cast<DHCPOptions*>(this)->getServerIdentifier();}
    virtual void setServerIdentifier(const IPv4Address& serverIdentifier);
    virtual ::omnetpp::simtime_t getRenewalTime() const;
    virtual void setRenewalTime(::omnetpp::simtime_t renewalTime);
    virtual ::omnetpp::simtime_t getRebindingTime() const;
    virtual void setRebindingTime(::omnetpp::simtime_t rebindingTime);
    virtual ::omnetpp::simtime_t getLeaseTime() const;
    virtual void setLeaseTime(::omnetpp::simtime_t leaseTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DHCPOptions& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DHCPOptions& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/applications/dhcp/DHCPMessage.msg:97</tt> by nedtool.
 * <pre>
 * //
 * // Represents a DHCP message. DHCP (Dynamic Host Configuration Protocol, RFC 2131)
 * // provides a framework for passing configuration information to hosts on a TCP/IP network.
 * //
 * // \@see DHCPClient, DHCPServer
 * //
 * packet DHCPMessage
 * {
 *     int op \@enum(DHCPOpcode); // message op code / message type. 1 = BOOTREQUEST, 2 = BOOTREPLY
 *     int htype; // hardware address type, see ARP section in "Assigned Numbers" RFC; e.g., '1' = 10mb ethernet
 *     int hlen; // hardware address length (e.g.  '6' for 10mb ethernet)
 *     int hops; // client sets to zero, optionally used by relay agents when booting via a relay agent
 *     unsigned int xid; // transaction ID, a random number chosen by the client, used by the client and server to associate messages and responses between a client and a server
 *     int secs; // filled in by client, seconds elapsed since client began address acquisition or renewal process
 *     bool broadcast; // the broadcast bit in the flags field
 *     IPv4Address ciaddr; // client IP address; only filled in if client is in BOUND, RENEW or REBINDING state and can respond to ARP requests
 *     IPv4Address yiaddr; // 'your' (client) IP address
 *     IPv4Address giaddr; // relay agent IP address, used in booting via a relay agent
 *     MACAddress chaddr; // client hardware address (MAC)
 *     string sname; // optional server host name
 *     string file; // boot file name (unused in the simulation)
 *     DHCPOptions options; // holds DHCP options
 * }
 * </pre>
 */
class INET_API DHCPMessage : public ::omnetpp::cPacket
{
  protected:
    int op;
    int htype;
    int hlen;
    int hops;
    unsigned int xid;
    int secs;
    bool broadcast;
    IPv4Address ciaddr;
    IPv4Address yiaddr;
    IPv4Address giaddr;
    MACAddress chaddr;
    ::omnetpp::opp_string sname;
    ::omnetpp::opp_string file;
    DHCPOptions options;

  private:
    void copy(const DHCPMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DHCPMessage&);

  public:
    DHCPMessage(const char *name=nullptr, short kind=0);
    DHCPMessage(const DHCPMessage& other);
    virtual ~DHCPMessage();
    DHCPMessage& operator=(const DHCPMessage& other);
    virtual DHCPMessage *dup() const override {return new DHCPMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getOp() const;
    virtual void setOp(int op);
    virtual int getHtype() const;
    virtual void setHtype(int htype);
    virtual int getHlen() const;
    virtual void setHlen(int hlen);
    virtual int getHops() const;
    virtual void setHops(int hops);
    virtual unsigned int getXid() const;
    virtual void setXid(unsigned int xid);
    virtual int getSecs() const;
    virtual void setSecs(int secs);
    virtual bool getBroadcast() const;
    virtual void setBroadcast(bool broadcast);
    virtual IPv4Address& getCiaddr();
    virtual const IPv4Address& getCiaddr() const {return const_cast<DHCPMessage*>(this)->getCiaddr();}
    virtual void setCiaddr(const IPv4Address& ciaddr);
    virtual IPv4Address& getYiaddr();
    virtual const IPv4Address& getYiaddr() const {return const_cast<DHCPMessage*>(this)->getYiaddr();}
    virtual void setYiaddr(const IPv4Address& yiaddr);
    virtual IPv4Address& getGiaddr();
    virtual const IPv4Address& getGiaddr() const {return const_cast<DHCPMessage*>(this)->getGiaddr();}
    virtual void setGiaddr(const IPv4Address& giaddr);
    virtual MACAddress& getChaddr();
    virtual const MACAddress& getChaddr() const {return const_cast<DHCPMessage*>(this)->getChaddr();}
    virtual void setChaddr(const MACAddress& chaddr);
    virtual const char * getSname() const;
    virtual void setSname(const char * sname);
    virtual const char * getFile() const;
    virtual void setFile(const char * file);
    virtual DHCPOptions& getOptions();
    virtual const DHCPOptions& getOptions() const {return const_cast<DHCPMessage*>(this)->getOptions();}
    virtual void setOptions(const DHCPOptions& options);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DHCPMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DHCPMessage& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_DHCPMESSAGE_M_H
