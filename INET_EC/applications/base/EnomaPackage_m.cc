//
// Generated file, do not edit! Created by nedtool 5.1 from inet/applications/base/EnomaPackage.msg.
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
#include "EnomaPackage_m.h"

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

Register_Class(EnomaPackage)

EnomaPackage::EnomaPackage(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->msgType = 0;
    this->size = 0;
    this->cacheSize = 0;
    this->mips = 0;
}

EnomaPackage::EnomaPackage(const EnomaPackage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EnomaPackage::~EnomaPackage()
{
}

EnomaPackage& EnomaPackage::operator=(const EnomaPackage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EnomaPackage::copy(const EnomaPackage& other)
{
    this->msgType = other.msgType;
    this->ueIp = other.ueIp;
    this->sp = other.sp;
    this->size = other.size;
    this->cacheSize = other.cacheSize;
    this->mips = other.mips;
    this->listEdgeService = other.listEdgeService;
    this->nodeName = other.nodeName;
}

void EnomaPackage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->msgType);
    doParsimPacking(b,this->ueIp);
    doParsimPacking(b,this->sp);
    doParsimPacking(b,this->size);
    doParsimPacking(b,this->cacheSize);
    doParsimPacking(b,this->mips);
    doParsimPacking(b,this->listEdgeService);
    doParsimPacking(b,this->nodeName);
}

void EnomaPackage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->msgType);
    doParsimUnpacking(b,this->ueIp);
    doParsimUnpacking(b,this->sp);
    doParsimUnpacking(b,this->size);
    doParsimUnpacking(b,this->cacheSize);
    doParsimUnpacking(b,this->mips);
    doParsimUnpacking(b,this->listEdgeService);
    doParsimUnpacking(b,this->nodeName);
}

int EnomaPackage::getMsgType() const
{
    return this->msgType;
}

void EnomaPackage::setMsgType(int msgType)
{
    this->msgType = msgType;
}

const char * EnomaPackage::getUeIp() const
{
    return this->ueIp.c_str();
}

void EnomaPackage::setUeIp(const char * ueIp)
{
    this->ueIp = ueIp;
}

const char * EnomaPackage::getSp() const
{
    return this->sp.c_str();
}

void EnomaPackage::setSp(const char * sp)
{
    this->sp = sp;
}

int EnomaPackage::getSize() const
{
    return this->size;
}

void EnomaPackage::setSize(int size)
{
    this->size = size;
}

int EnomaPackage::getCacheSize() const
{
    return this->cacheSize;
}

void EnomaPackage::setCacheSize(int cacheSize)
{
    this->cacheSize = cacheSize;
}

int EnomaPackage::getMips() const
{
    return this->mips;
}

void EnomaPackage::setMips(int mips)
{
    this->mips = mips;
}

const char * EnomaPackage::getListEdgeService() const
{
    return this->listEdgeService.c_str();
}

void EnomaPackage::setListEdgeService(const char * listEdgeService)
{
    this->listEdgeService = listEdgeService;
}

const char * EnomaPackage::getNodeName() const
{
    return this->nodeName.c_str();
}

void EnomaPackage::setNodeName(const char * nodeName)
{
    this->nodeName = nodeName;
}

class EnomaPackageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    EnomaPackageDescriptor();
    virtual ~EnomaPackageDescriptor();

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

Register_ClassDescriptor(EnomaPackageDescriptor)

EnomaPackageDescriptor::EnomaPackageDescriptor() : omnetpp::cClassDescriptor("inet::EnomaPackage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

EnomaPackageDescriptor::~EnomaPackageDescriptor()
{
    delete[] propertynames;
}

bool EnomaPackageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EnomaPackage *>(obj)!=nullptr;
}

const char **EnomaPackageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *EnomaPackageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int EnomaPackageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int EnomaPackageDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *EnomaPackageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "msgType",
        "ueIp",
        "sp",
        "size",
        "cacheSize",
        "mips",
        "listEdgeService",
        "nodeName",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int EnomaPackageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgType")==0) return base+0;
    if (fieldName[0]=='u' && strcmp(fieldName, "ueIp")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sp")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "size")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "cacheSize")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "mips")==0) return base+5;
    if (fieldName[0]=='l' && strcmp(fieldName, "listEdgeService")==0) return base+6;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeName")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *EnomaPackageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "string",
        "int",
        "int",
        "int",
        "string",
        "string",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **EnomaPackageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EnomaPackageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EnomaPackageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    EnomaPackage *pp = (EnomaPackage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *EnomaPackageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EnomaPackage *pp = (EnomaPackage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EnomaPackageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    EnomaPackage *pp = (EnomaPackage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMsgType());
        case 1: return oppstring2string(pp->getUeIp());
        case 2: return oppstring2string(pp->getSp());
        case 3: return long2string(pp->getSize());
        case 4: return long2string(pp->getCacheSize());
        case 5: return long2string(pp->getMips());
        case 6: return oppstring2string(pp->getListEdgeService());
        case 7: return oppstring2string(pp->getNodeName());
        default: return "";
    }
}

bool EnomaPackageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    EnomaPackage *pp = (EnomaPackage *)object; (void)pp;
    switch (field) {
        case 0: pp->setMsgType(string2long(value)); return true;
        case 1: pp->setUeIp((value)); return true;
        case 2: pp->setSp((value)); return true;
        case 3: pp->setSize(string2long(value)); return true;
        case 4: pp->setCacheSize(string2long(value)); return true;
        case 5: pp->setMips(string2long(value)); return true;
        case 6: pp->setListEdgeService((value)); return true;
        case 7: pp->setNodeName((value)); return true;
        default: return false;
    }
}

const char *EnomaPackageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *EnomaPackageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    EnomaPackage *pp = (EnomaPackage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet

