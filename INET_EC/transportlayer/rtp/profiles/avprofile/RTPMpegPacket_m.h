//
// Generated file, do not edit! Created by nedtool 5.1 from inet/transportlayer/rtp/profiles/avprofile/RTPMpegPacket.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __INET__RTP_RTPMPEGPACKET_M_H
#define __INET__RTP_RTPMPEGPACKET_M_H

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


namespace inet {
namespace rtp {

/**
 * Class generated from <tt>inet/transportlayer/rtp/profiles/avprofile/RTPMpegPacket.msg:36</tt> by nedtool.
 * <pre>
 * packet RTPMpegPacket
 * {
 *     int headerLength = 4;
 *     int payloadLength; // size of the mpeg data
 *     int pictureType;   // picture type of the frame the data in this packet belongs to.
 * 
 *     // currenrtly unused fields:
 *     //int mzb;
 *     //int two;
 *     //int temporalReference;
 *     //int activeN;
 *     //int newPictureHeader;
 *     //int sequenceHeaderPresent;
 *     //int beginningOfSlice;
 *     //int endOfSlice;
 *     //int fbv;
 *     //int bfc;
 *     //int ffv;
 *     //int ffc;
 * }
 * </pre>
 */
class INET_API RTPMpegPacket : public ::omnetpp::cPacket
{
  protected:
    int headerLength;
    int payloadLength;
    int pictureType;

  private:
    void copy(const RTPMpegPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const RTPMpegPacket&);

  public:
    RTPMpegPacket(const char *name=nullptr, short kind=0);
    RTPMpegPacket(const RTPMpegPacket& other);
    virtual ~RTPMpegPacket();
    RTPMpegPacket& operator=(const RTPMpegPacket& other);
    virtual RTPMpegPacket *dup() const override {return new RTPMpegPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getHeaderLength() const;
    virtual void setHeaderLength(int headerLength);
    virtual int getPayloadLength() const;
    virtual void setPayloadLength(int payloadLength);
    virtual int getPictureType() const;
    virtual void setPictureType(int pictureType);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RTPMpegPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RTPMpegPacket& obj) {obj.parsimUnpack(b);}

} // namespace rtp
} // namespace inet

#endif // ifndef __INET__RTP_RTPMPEGPACKET_M_H

