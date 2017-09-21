//
// Generated file, do not edit! Created by nedtool 5.1 from inet_bk/applications/voipstream/VoIPStreamPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "VoIPStreamPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::VoIPStreamPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::VoIPStreamPacketType"));
    e->insert(VOICE, "VOICE");
    e->insert(SILENCE, "SILENCE");
)

Register_Class(VoIPStreamPacket)

VoIPStreamPacket::VoIPStreamPacket(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->type = 0;
    this->codec = 0;
    this->sampleBits = 0;
    this->sampleRate = 0;
    this->transmitBitrate = 0;
    this->samplesPerPacket = 0;
    this->seqNo = 0;
    this->timeStamp = 0;
    this->ssrc = 0;
}

VoIPStreamPacket::VoIPStreamPacket(const VoIPStreamPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

VoIPStreamPacket::~VoIPStreamPacket()
{
}

VoIPStreamPacket& VoIPStreamPacket::operator=(const VoIPStreamPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VoIPStreamPacket::copy(const VoIPStreamPacket& other)
{
    this->type = other.type;
    this->codec = other.codec;
    this->sampleBits = other.sampleBits;
    this->sampleRate = other.sampleRate;
    this->transmitBitrate = other.transmitBitrate;
    this->samplesPerPacket = other.samplesPerPacket;
    this->bytes = other.bytes;
    this->seqNo = other.seqNo;
    this->timeStamp = other.timeStamp;
    this->ssrc = other.ssrc;
}

void VoIPStreamPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->codec);
    doParsimPacking(b,this->sampleBits);
    doParsimPacking(b,this->sampleRate);
    doParsimPacking(b,this->transmitBitrate);
    doParsimPacking(b,this->samplesPerPacket);
    doParsimPacking(b,this->bytes);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->timeStamp);
    doParsimPacking(b,this->ssrc);
}

void VoIPStreamPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->codec);
    doParsimUnpacking(b,this->sampleBits);
    doParsimUnpacking(b,this->sampleRate);
    doParsimUnpacking(b,this->transmitBitrate);
    doParsimUnpacking(b,this->samplesPerPacket);
    doParsimUnpacking(b,this->bytes);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->timeStamp);
    doParsimUnpacking(b,this->ssrc);
}

int VoIPStreamPacket::getType() const
{
    return this->type;
}

void VoIPStreamPacket::setType(int type)
{
    this->type = type;
}

int VoIPStreamPacket::getCodec() const
{
    return this->codec;
}

void VoIPStreamPacket::setCodec(int codec)
{
    this->codec = codec;
}

short VoIPStreamPacket::getSampleBits() const
{
    return this->sampleBits;
}

void VoIPStreamPacket::setSampleBits(short sampleBits)
{
    this->sampleBits = sampleBits;
}

int VoIPStreamPacket::getSampleRate() const
{
    return this->sampleRate;
}

void VoIPStreamPacket::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
}

int VoIPStreamPacket::getTransmitBitrate() const
{
    return this->transmitBitrate;
}

void VoIPStreamPacket::setTransmitBitrate(int transmitBitrate)
{
    this->transmitBitrate = transmitBitrate;
}

int VoIPStreamPacket::getSamplesPerPacket() const
{
    return this->samplesPerPacket;
}

void VoIPStreamPacket::setSamplesPerPacket(int samplesPerPacket)
{
    this->samplesPerPacket = samplesPerPacket;
}

ByteArray& VoIPStreamPacket::getBytes()
{
    return this->bytes;
}

void VoIPStreamPacket::setBytes(const ByteArray& bytes)
{
    this->bytes = bytes;
}

uint16_t VoIPStreamPacket::getSeqNo() const
{
    return this->seqNo;
}

void VoIPStreamPacket::setSeqNo(uint16_t seqNo)
{
    this->seqNo = seqNo;
}

uint32_t VoIPStreamPacket::getTimeStamp() const
{
    return this->timeStamp;
}

void VoIPStreamPacket::setTimeStamp(uint32_t timeStamp)
{
    this->timeStamp = timeStamp;
}

uint32_t VoIPStreamPacket::getSsrc() const
{
    return this->ssrc;
}

void VoIPStreamPacket::setSsrc(uint32_t ssrc)
{
    this->ssrc = ssrc;
}

class VoIPStreamPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    VoIPStreamPacketDescriptor();
    virtual ~VoIPStreamPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(VoIPStreamPacketDescriptor)

VoIPStreamPacketDescriptor::VoIPStreamPacketDescriptor() : omnetpp::cClassDescriptor("inet::VoIPStreamPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

VoIPStreamPacketDescriptor::~VoIPStreamPacketDescriptor()
{
    delete[] propertynames;
}

bool VoIPStreamPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VoIPStreamPacket *>(obj)!=nullptr;
}

const char **VoIPStreamPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *VoIPStreamPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int VoIPStreamPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount() : 10;
}

unsigned int VoIPStreamPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *VoIPStreamPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "codec",
        "sampleBits",
        "sampleRate",
        "transmitBitrate",
        "samplesPerPacket",
        "bytes",
        "seqNo",
        "timeStamp",
        "ssrc",
    };
    return (field>=0 && field<10) ? fieldNames[field] : nullptr;
}

int VoIPStreamPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "codec")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sampleBits")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sampleRate")==0) return base+3;
    if (fieldName[0]=='t' && strcmp(fieldName, "transmitBitrate")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "samplesPerPacket")==0) return base+5;
    if (fieldName[0]=='b' && strcmp(fieldName, "bytes")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNo")==0) return base+7;
    if (fieldName[0]=='t' && strcmp(fieldName, "timeStamp")==0) return base+8;
    if (fieldName[0]=='s' && strcmp(fieldName, "ssrc")==0) return base+9;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *VoIPStreamPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "short",
        "int",
        "int",
        "int",
        "ByteArray",
        "uint16_t",
        "uint32_t",
        "uint32_t",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : nullptr;
}

const char **VoIPStreamPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *VoIPStreamPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "inet::VoIPStreamPacketType";
            return nullptr;
        default: return nullptr;
    }
}

int VoIPStreamPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    VoIPStreamPacket *pp = (VoIPStreamPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *VoIPStreamPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    VoIPStreamPacket *pp = (VoIPStreamPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VoIPStreamPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    VoIPStreamPacket *pp = (VoIPStreamPacket *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getType(), "inet::VoIPStreamPacketType");
        case 1: return long2string(pp->getCodec());
        case 2: return long2string(pp->getSampleBits());
        case 3: return long2string(pp->getSampleRate());
        case 4: return long2string(pp->getTransmitBitrate());
        case 5: return long2string(pp->getSamplesPerPacket());
        case 6: {std::stringstream out; out << pp->getBytes(); return out.str();}
        case 7: return ulong2string(pp->getSeqNo());
        case 8: return ulong2string(pp->getTimeStamp());
        case 9: return ulong2string(pp->getSsrc());
        default: return "";
    }
}

bool VoIPStreamPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    VoIPStreamPacket *pp = (VoIPStreamPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setType((inet::VoIPStreamPacketType)string2enum(value, "inet::VoIPStreamPacketType")); return true;
        case 1: pp->setCodec(string2long(value)); return true;
        case 2: pp->setSampleBits(string2long(value)); return true;
        case 3: pp->setSampleRate(string2long(value)); return true;
        case 4: pp->setTransmitBitrate(string2long(value)); return true;
        case 5: pp->setSamplesPerPacket(string2long(value)); return true;
        case 7: pp->setSeqNo(string2ulong(value)); return true;
        case 8: pp->setTimeStamp(string2ulong(value)); return true;
        case 9: pp->setSsrc(string2ulong(value)); return true;
        default: return false;
    }
}

const char *VoIPStreamPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 6: return omnetpp::opp_typename(typeid(ByteArray));
        default: return nullptr;
    };
}

void *VoIPStreamPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    VoIPStreamPacket *pp = (VoIPStreamPacket *)object; (void)pp;
    switch (field) {
        case 6: return (void *)(&pp->getBytes()); break;
        default: return nullptr;
    }
}

} // namespace inet

