// Created by Larry


package inet.applications.udpapp;

import inet.applications.contract.IUDPApp;


//
// Sends UDP packets to the given IP address at the given interval.
// Compatible with both ~IPv4 and ~IPv6.
//
// The sending interval can be a constant or a random value (e.g. exponential(1)).
// If the destAddresses parameter contains more than one address, one
// of them is randomly chosen for each packet. An address may be given in the
// dotted decimal notation, or with the module name. (The L3AddressResolver
// class is used to resolve the address.) To disable the model, set
// destAddresses to "".
//
// Received packets are discarded.
//
// The peer can be a ~UDPSink, another ~UDPBasicApp (it handles received packets
// like ~UDPSink), or a ~UDPEchoApp. When used with ~UDPEchoApp, the rcvdPkLifetime
// statistic will contain the round-trip times.
//
simple UDPEdgeApp like IUDPApp
{
    parameters:
        string interfaceTableModule;   // The path to the InterfaceTable module
        string serviceTableModule;
        int localPort = default(-1);  // local port (-1: use ephemeral port)
        int enomaPort = default(-1);
        int isEnoma = default(-1);
        int isEdgeNode = default(-1);
        int isSP = default(-1);
        int size = default(0); //in Mb
        int cacheSize = default(0); // in Mb
        int mips = default(0);
        string destAddresses = default(""); // list of IP addresses, separated by spaces ("": don't send)
        string enomaAddresses = default("");
        string localAddress = default("");
        string packetName = default("UDPEdgeAppData");
        int destPort;
        volatile int messageLength @unit(B); // length of messages to generate, in bytes
        double startTime @unit(s) = default(this.sendInterval); // application start time (start of the first packet)
        double stopTime @unit(s) = default(-1s);  // time of finishing sending, -1s means forever
        double disable_service_interval @unit(s) = default(0s);
        volatile double sendInterval @unit(s); // should usually be a random value, e.g. exponential(1)
        int timeToLive = default(-1); // if not -1, set the TTL (IPv4) or Hop Limit (IPv6) field of sent packets to this value
        int typeOfService = default(-1); // if not -1, set the ToS (IPv4) or Traffic Class (IPv6) field of sent packets to this value
        string multicastInterface = default("");  // if not empty, set the multicast output interface option on the socket (interface name expected)
        bool receiveBroadcast = default(false); // if true, makes the socket receive broadcast packets
        bool joinLocalMulticastGroups = default(false); // if true, makes the socket receive packets from all multicast groups set on local interfaces        
        @display("i=block/app");
        @signal[sentPk](type=cPacket);
        @signal[rcvdPk](type=cPacket);
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[throughput](title="throughput"; unit=bps; source="throughput(rcvdPk)"; record=vector);
        @statistic[sentPk](title="packets sent"; source=sentPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[rcvdPkLifetime](title="received packet lifetime"; source="messageAge(rcvdPk)"; unit=s; record=stats,vector; interpolationmode=none);
        @statistic[rcvdPkSeqNo](title="received packet sequence number"; source="appPkSeqNo(rcvdPk)"; record=vector; interpolationmode=none);
    gates:
        input udpIn @labels(UDPControlInfo/up);
        output udpOut @labels(UDPControlInfo/down);
}
