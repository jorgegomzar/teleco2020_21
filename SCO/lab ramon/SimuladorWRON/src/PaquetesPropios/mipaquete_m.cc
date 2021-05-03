//
// Generated file, do not edit! Created by nedtool 5.6 from src/PaquetesPropios/mipaquete.msg.
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
#include "mipaquete_m.h"

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

Register_Class(PeticionLightpath)

PeticionLightpath::PeticionLightpath(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->nodo_origen = 0;
    this->nodo_destino = 0;
    this->tiempo_servicio = 0;
}

PeticionLightpath::PeticionLightpath(const PeticionLightpath& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PeticionLightpath::~PeticionLightpath()
{
}

PeticionLightpath& PeticionLightpath::operator=(const PeticionLightpath& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PeticionLightpath::copy(const PeticionLightpath& other)
{
    this->nodo_origen = other.nodo_origen;
    this->nodo_destino = other.nodo_destino;
    this->tiempo_servicio = other.tiempo_servicio;
}

void PeticionLightpath::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->nodo_origen);
    doParsimPacking(b,this->nodo_destino);
    doParsimPacking(b,this->tiempo_servicio);
}

void PeticionLightpath::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->nodo_origen);
    doParsimUnpacking(b,this->nodo_destino);
    doParsimUnpacking(b,this->tiempo_servicio);
}

int PeticionLightpath::getNodo_origen() const
{
    return this->nodo_origen;
}

void PeticionLightpath::setNodo_origen(int nodo_origen)
{
    this->nodo_origen = nodo_origen;
}

int PeticionLightpath::getNodo_destino() const
{
    return this->nodo_destino;
}

void PeticionLightpath::setNodo_destino(int nodo_destino)
{
    this->nodo_destino = nodo_destino;
}

double PeticionLightpath::getTiempo_servicio() const
{
    return this->tiempo_servicio;
}

void PeticionLightpath::setTiempo_servicio(double tiempo_servicio)
{
    this->tiempo_servicio = tiempo_servicio;
}

class PeticionLightpathDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PeticionLightpathDescriptor();
    virtual ~PeticionLightpathDescriptor();

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

Register_ClassDescriptor(PeticionLightpathDescriptor)

PeticionLightpathDescriptor::PeticionLightpathDescriptor() : omnetpp::cClassDescriptor("PeticionLightpath", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

PeticionLightpathDescriptor::~PeticionLightpathDescriptor()
{
    delete[] propertynames;
}

bool PeticionLightpathDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PeticionLightpath *>(obj)!=nullptr;
}

const char **PeticionLightpathDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PeticionLightpathDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PeticionLightpathDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int PeticionLightpathDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *PeticionLightpathDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodo_origen",
        "nodo_destino",
        "tiempo_servicio",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int PeticionLightpathDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodo_origen")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodo_destino")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "tiempo_servicio")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PeticionLightpathDescriptor::getFieldTypeString(int field) const
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
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **PeticionLightpathDescriptor::getFieldPropertyNames(int field) const
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

const char *PeticionLightpathDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int PeticionLightpathDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PeticionLightpath *pp = (PeticionLightpath *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PeticionLightpathDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PeticionLightpath *pp = (PeticionLightpath *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PeticionLightpathDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PeticionLightpath *pp = (PeticionLightpath *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodo_origen());
        case 1: return long2string(pp->getNodo_destino());
        case 2: return double2string(pp->getTiempo_servicio());
        default: return "";
    }
}

bool PeticionLightpathDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PeticionLightpath *pp = (PeticionLightpath *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodo_origen(string2long(value)); return true;
        case 1: pp->setNodo_destino(string2long(value)); return true;
        case 2: pp->setTiempo_servicio(string2double(value)); return true;
        default: return false;
    }
}

const char *PeticionLightpathDescriptor::getFieldStructName(int field) const
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

void *PeticionLightpathDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PeticionLightpath *pp = (PeticionLightpath *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(RutaYLong)

RutaYLong::RutaYLong(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->nodo_origen = 0;
    this->nodo_destino = 0;
    this->tiempo_servicio = 0;
    this->longitud_onda = 0;
    ruta_arraysize = 0;
    this->ruta = 0;
    this->longitud_onda_proteccion = 0;
    ruta_proteccion_arraysize = 0;
    this->ruta_proteccion = 0;
    this->proteccion_activada = false;
}

RutaYLong::RutaYLong(const RutaYLong& other) : ::omnetpp::cMessage(other)
{
    ruta_arraysize = 0;
    this->ruta = 0;
    ruta_proteccion_arraysize = 0;
    this->ruta_proteccion = 0;
    copy(other);
}

RutaYLong::~RutaYLong()
{
    delete [] this->ruta;
    delete [] this->ruta_proteccion;
}

RutaYLong& RutaYLong::operator=(const RutaYLong& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RutaYLong::copy(const RutaYLong& other)
{
    this->nodo_origen = other.nodo_origen;
    this->nodo_destino = other.nodo_destino;
    this->tiempo_servicio = other.tiempo_servicio;
    this->longitud_onda = other.longitud_onda;
    delete [] this->ruta;
    this->ruta = (other.ruta_arraysize==0) ? nullptr : new int[other.ruta_arraysize];
    ruta_arraysize = other.ruta_arraysize;
    for (unsigned int i=0; i<ruta_arraysize; i++)
        this->ruta[i] = other.ruta[i];
    this->longitud_onda_proteccion = other.longitud_onda_proteccion;
    delete [] this->ruta_proteccion;
    this->ruta_proteccion = (other.ruta_proteccion_arraysize==0) ? nullptr : new int[other.ruta_proteccion_arraysize];
    ruta_proteccion_arraysize = other.ruta_proteccion_arraysize;
    for (unsigned int i=0; i<ruta_proteccion_arraysize; i++)
        this->ruta_proteccion[i] = other.ruta_proteccion[i];
    this->proteccion_activada = other.proteccion_activada;
}

void RutaYLong::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->nodo_origen);
    doParsimPacking(b,this->nodo_destino);
    doParsimPacking(b,this->tiempo_servicio);
    doParsimPacking(b,this->longitud_onda);
    b->pack(ruta_arraysize);
    doParsimArrayPacking(b,this->ruta,ruta_arraysize);
    doParsimPacking(b,this->longitud_onda_proteccion);
    b->pack(ruta_proteccion_arraysize);
    doParsimArrayPacking(b,this->ruta_proteccion,ruta_proteccion_arraysize);
    doParsimPacking(b,this->proteccion_activada);
}

void RutaYLong::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->nodo_origen);
    doParsimUnpacking(b,this->nodo_destino);
    doParsimUnpacking(b,this->tiempo_servicio);
    doParsimUnpacking(b,this->longitud_onda);
    delete [] this->ruta;
    b->unpack(ruta_arraysize);
    if (ruta_arraysize==0) {
        this->ruta = 0;
    } else {
        this->ruta = new int[ruta_arraysize];
        doParsimArrayUnpacking(b,this->ruta,ruta_arraysize);
    }
    doParsimUnpacking(b,this->longitud_onda_proteccion);
    delete [] this->ruta_proteccion;
    b->unpack(ruta_proteccion_arraysize);
    if (ruta_proteccion_arraysize==0) {
        this->ruta_proteccion = 0;
    } else {
        this->ruta_proteccion = new int[ruta_proteccion_arraysize];
        doParsimArrayUnpacking(b,this->ruta_proteccion,ruta_proteccion_arraysize);
    }
    doParsimUnpacking(b,this->proteccion_activada);
}

int RutaYLong::getNodo_origen() const
{
    return this->nodo_origen;
}

void RutaYLong::setNodo_origen(int nodo_origen)
{
    this->nodo_origen = nodo_origen;
}

int RutaYLong::getNodo_destino() const
{
    return this->nodo_destino;
}

void RutaYLong::setNodo_destino(int nodo_destino)
{
    this->nodo_destino = nodo_destino;
}

double RutaYLong::getTiempo_servicio() const
{
    return this->tiempo_servicio;
}

void RutaYLong::setTiempo_servicio(double tiempo_servicio)
{
    this->tiempo_servicio = tiempo_servicio;
}

int RutaYLong::getLongitud_onda() const
{
    return this->longitud_onda;
}

void RutaYLong::setLongitud_onda(int longitud_onda)
{
    this->longitud_onda = longitud_onda;
}

void RutaYLong::setRutaArraySize(unsigned int size)
{
    int *ruta2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = ruta_arraysize < size ? ruta_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        ruta2[i] = this->ruta[i];
    for (unsigned int i=sz; i<size; i++)
        ruta2[i] = 0;
    ruta_arraysize = size;
    delete [] this->ruta;
    this->ruta = ruta2;
}

unsigned int RutaYLong::getRutaArraySize() const
{
    return ruta_arraysize;
}

int RutaYLong::getRuta(unsigned int k) const
{
    if (k>=ruta_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", ruta_arraysize, k);
    return this->ruta[k];
}

void RutaYLong::setRuta(unsigned int k, int ruta)
{
    if (k>=ruta_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", ruta_arraysize, k);
    this->ruta[k] = ruta;
}

int RutaYLong::getLongitud_onda_proteccion() const
{
    return this->longitud_onda_proteccion;
}

void RutaYLong::setLongitud_onda_proteccion(int longitud_onda_proteccion)
{
    this->longitud_onda_proteccion = longitud_onda_proteccion;
}

void RutaYLong::setRuta_proteccionArraySize(unsigned int size)
{
    int *ruta_proteccion2 = (size==0) ? nullptr : new int[size];
    unsigned int sz = ruta_proteccion_arraysize < size ? ruta_proteccion_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        ruta_proteccion2[i] = this->ruta_proteccion[i];
    for (unsigned int i=sz; i<size; i++)
        ruta_proteccion2[i] = 0;
    ruta_proteccion_arraysize = size;
    delete [] this->ruta_proteccion;
    this->ruta_proteccion = ruta_proteccion2;
}

unsigned int RutaYLong::getRuta_proteccionArraySize() const
{
    return ruta_proteccion_arraysize;
}

int RutaYLong::getRuta_proteccion(unsigned int k) const
{
    if (k>=ruta_proteccion_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", ruta_proteccion_arraysize, k);
    return this->ruta_proteccion[k];
}

void RutaYLong::setRuta_proteccion(unsigned int k, int ruta_proteccion)
{
    if (k>=ruta_proteccion_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", ruta_proteccion_arraysize, k);
    this->ruta_proteccion[k] = ruta_proteccion;
}

bool RutaYLong::getProteccion_activada() const
{
    return this->proteccion_activada;
}

void RutaYLong::setProteccion_activada(bool proteccion_activada)
{
    this->proteccion_activada = proteccion_activada;
}

class RutaYLongDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RutaYLongDescriptor();
    virtual ~RutaYLongDescriptor();

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

Register_ClassDescriptor(RutaYLongDescriptor)

RutaYLongDescriptor::RutaYLongDescriptor() : omnetpp::cClassDescriptor("RutaYLong", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

RutaYLongDescriptor::~RutaYLongDescriptor()
{
    delete[] propertynames;
}

bool RutaYLongDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RutaYLong *>(obj)!=nullptr;
}

const char **RutaYLongDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RutaYLongDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RutaYLongDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int RutaYLongDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *RutaYLongDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodo_origen",
        "nodo_destino",
        "tiempo_servicio",
        "longitud_onda",
        "ruta",
        "longitud_onda_proteccion",
        "ruta_proteccion",
        "proteccion_activada",
    };
    return (field>=0 && field<8) ? fieldNames[field] : nullptr;
}

int RutaYLongDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodo_origen")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodo_destino")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "tiempo_servicio")==0) return base+2;
    if (fieldName[0]=='l' && strcmp(fieldName, "longitud_onda")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "ruta")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "longitud_onda_proteccion")==0) return base+5;
    if (fieldName[0]=='r' && strcmp(fieldName, "ruta_proteccion")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "proteccion_activada")==0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RutaYLongDescriptor::getFieldTypeString(int field) const
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
        "double",
        "int",
        "int",
        "int",
        "int",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : nullptr;
}

const char **RutaYLongDescriptor::getFieldPropertyNames(int field) const
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

const char *RutaYLongDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int RutaYLongDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RutaYLong *pp = (RutaYLong *)object; (void)pp;
    switch (field) {
        case 4: return pp->getRutaArraySize();
        case 6: return pp->getRuta_proteccionArraySize();
        default: return 0;
    }
}

const char *RutaYLongDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RutaYLong *pp = (RutaYLong *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RutaYLongDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RutaYLong *pp = (RutaYLong *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodo_origen());
        case 1: return long2string(pp->getNodo_destino());
        case 2: return double2string(pp->getTiempo_servicio());
        case 3: return long2string(pp->getLongitud_onda());
        case 4: return long2string(pp->getRuta(i));
        case 5: return long2string(pp->getLongitud_onda_proteccion());
        case 6: return long2string(pp->getRuta_proteccion(i));
        case 7: return bool2string(pp->getProteccion_activada());
        default: return "";
    }
}

bool RutaYLongDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RutaYLong *pp = (RutaYLong *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodo_origen(string2long(value)); return true;
        case 1: pp->setNodo_destino(string2long(value)); return true;
        case 2: pp->setTiempo_servicio(string2double(value)); return true;
        case 3: pp->setLongitud_onda(string2long(value)); return true;
        case 4: pp->setRuta(i,string2long(value)); return true;
        case 5: pp->setLongitud_onda_proteccion(string2long(value)); return true;
        case 6: pp->setRuta_proteccion(i,string2long(value)); return true;
        case 7: pp->setProteccion_activada(string2bool(value)); return true;
        default: return false;
    }
}

const char *RutaYLongDescriptor::getFieldStructName(int field) const
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

void *RutaYLongDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RutaYLong *pp = (RutaYLong *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(CargaNodo)

CargaNodo::CargaNodo(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    carga_arraysize = 0;
    this->carga = 0;
    this->nodo = 0;
}

CargaNodo::CargaNodo(const CargaNodo& other) : ::omnetpp::cMessage(other)
{
    carga_arraysize = 0;
    this->carga = 0;
    copy(other);
}

CargaNodo::~CargaNodo()
{
    delete [] this->carga;
}

CargaNodo& CargaNodo::operator=(const CargaNodo& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CargaNodo::copy(const CargaNodo& other)
{
    delete [] this->carga;
    this->carga = (other.carga_arraysize==0) ? nullptr : new double[other.carga_arraysize];
    carga_arraysize = other.carga_arraysize;
    for (unsigned int i=0; i<carga_arraysize; i++)
        this->carga[i] = other.carga[i];
    this->nodo = other.nodo;
}

void CargaNodo::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    b->pack(carga_arraysize);
    doParsimArrayPacking(b,this->carga,carga_arraysize);
    doParsimPacking(b,this->nodo);
}

void CargaNodo::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    delete [] this->carga;
    b->unpack(carga_arraysize);
    if (carga_arraysize==0) {
        this->carga = 0;
    } else {
        this->carga = new double[carga_arraysize];
        doParsimArrayUnpacking(b,this->carga,carga_arraysize);
    }
    doParsimUnpacking(b,this->nodo);
}

void CargaNodo::setCargaArraySize(unsigned int size)
{
    double *carga2 = (size==0) ? nullptr : new double[size];
    unsigned int sz = carga_arraysize < size ? carga_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        carga2[i] = this->carga[i];
    for (unsigned int i=sz; i<size; i++)
        carga2[i] = 0;
    carga_arraysize = size;
    delete [] this->carga;
    this->carga = carga2;
}

unsigned int CargaNodo::getCargaArraySize() const
{
    return carga_arraysize;
}

double CargaNodo::getCarga(unsigned int k) const
{
    if (k>=carga_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", carga_arraysize, k);
    return this->carga[k];
}

void CargaNodo::setCarga(unsigned int k, double carga)
{
    if (k>=carga_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", carga_arraysize, k);
    this->carga[k] = carga;
}

int CargaNodo::getNodo() const
{
    return this->nodo;
}

void CargaNodo::setNodo(int nodo)
{
    this->nodo = nodo;
}

class CargaNodoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CargaNodoDescriptor();
    virtual ~CargaNodoDescriptor();

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

Register_ClassDescriptor(CargaNodoDescriptor)

CargaNodoDescriptor::CargaNodoDescriptor() : omnetpp::cClassDescriptor("CargaNodo", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

CargaNodoDescriptor::~CargaNodoDescriptor()
{
    delete[] propertynames;
}

bool CargaNodoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CargaNodo *>(obj)!=nullptr;
}

const char **CargaNodoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CargaNodoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CargaNodoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int CargaNodoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CargaNodoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "carga",
        "nodo",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int CargaNodoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "carga")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodo")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CargaNodoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **CargaNodoDescriptor::getFieldPropertyNames(int field) const
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

const char *CargaNodoDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int CargaNodoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CargaNodo *pp = (CargaNodo *)object; (void)pp;
    switch (field) {
        case 0: return pp->getCargaArraySize();
        default: return 0;
    }
}

const char *CargaNodoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CargaNodo *pp = (CargaNodo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CargaNodoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CargaNodo *pp = (CargaNodo *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getCarga(i));
        case 1: return long2string(pp->getNodo());
        default: return "";
    }
}

bool CargaNodoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CargaNodo *pp = (CargaNodo *)object; (void)pp;
    switch (field) {
        case 0: pp->setCarga(i,string2double(value)); return true;
        case 1: pp->setNodo(string2long(value)); return true;
        default: return false;
    }
}

const char *CargaNodoDescriptor::getFieldStructName(int field) const
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

void *CargaNodoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CargaNodo *pp = (CargaNodo *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(MatrizTrafico)

MatrizTrafico::MatrizTrafico(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    trafico_arraysize = 0;
    this->trafico = 0;
    this->cambiado = 0;
    this->calcular = 0;
}

MatrizTrafico::MatrizTrafico(const MatrizTrafico& other) : ::omnetpp::cMessage(other)
{
    trafico_arraysize = 0;
    this->trafico = 0;
    copy(other);
}

MatrizTrafico::~MatrizTrafico()
{
    delete [] this->trafico;
}

MatrizTrafico& MatrizTrafico::operator=(const MatrizTrafico& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void MatrizTrafico::copy(const MatrizTrafico& other)
{
    delete [] this->trafico;
    this->trafico = (other.trafico_arraysize==0) ? nullptr : new double[other.trafico_arraysize];
    trafico_arraysize = other.trafico_arraysize;
    for (unsigned int i=0; i<trafico_arraysize; i++)
        this->trafico[i] = other.trafico[i];
    this->cambiado = other.cambiado;
    this->calcular = other.calcular;
}

void MatrizTrafico::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    b->pack(trafico_arraysize);
    doParsimArrayPacking(b,this->trafico,trafico_arraysize);
    doParsimPacking(b,this->cambiado);
    doParsimPacking(b,this->calcular);
}

void MatrizTrafico::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    delete [] this->trafico;
    b->unpack(trafico_arraysize);
    if (trafico_arraysize==0) {
        this->trafico = 0;
    } else {
        this->trafico = new double[trafico_arraysize];
        doParsimArrayUnpacking(b,this->trafico,trafico_arraysize);
    }
    doParsimUnpacking(b,this->cambiado);
    doParsimUnpacking(b,this->calcular);
}

void MatrizTrafico::setTraficoArraySize(unsigned int size)
{
    double *trafico2 = (size==0) ? nullptr : new double[size];
    unsigned int sz = trafico_arraysize < size ? trafico_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        trafico2[i] = this->trafico[i];
    for (unsigned int i=sz; i<size; i++)
        trafico2[i] = 0;
    trafico_arraysize = size;
    delete [] this->trafico;
    this->trafico = trafico2;
}

unsigned int MatrizTrafico::getTraficoArraySize() const
{
    return trafico_arraysize;
}

double MatrizTrafico::getTrafico(unsigned int k) const
{
    if (k>=trafico_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", trafico_arraysize, k);
    return this->trafico[k];
}

void MatrizTrafico::setTrafico(unsigned int k, double trafico)
{
    if (k>=trafico_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", trafico_arraysize, k);
    this->trafico[k] = trafico;
}

int MatrizTrafico::getCambiado() const
{
    return this->cambiado;
}

void MatrizTrafico::setCambiado(int cambiado)
{
    this->cambiado = cambiado;
}

int MatrizTrafico::getCalcular() const
{
    return this->calcular;
}

void MatrizTrafico::setCalcular(int calcular)
{
    this->calcular = calcular;
}

class MatrizTraficoDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MatrizTraficoDescriptor();
    virtual ~MatrizTraficoDescriptor();

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

Register_ClassDescriptor(MatrizTraficoDescriptor)

MatrizTraficoDescriptor::MatrizTraficoDescriptor() : omnetpp::cClassDescriptor("MatrizTrafico", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

MatrizTraficoDescriptor::~MatrizTraficoDescriptor()
{
    delete[] propertynames;
}

bool MatrizTraficoDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MatrizTrafico *>(obj)!=nullptr;
}

const char **MatrizTraficoDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MatrizTraficoDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MatrizTraficoDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int MatrizTraficoDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *MatrizTraficoDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "trafico",
        "cambiado",
        "calcular",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int MatrizTraficoDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trafico")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cambiado")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "calcular")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MatrizTraficoDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **MatrizTraficoDescriptor::getFieldPropertyNames(int field) const
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

const char *MatrizTraficoDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int MatrizTraficoDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MatrizTrafico *pp = (MatrizTrafico *)object; (void)pp;
    switch (field) {
        case 0: return pp->getTraficoArraySize();
        default: return 0;
    }
}

const char *MatrizTraficoDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MatrizTrafico *pp = (MatrizTrafico *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MatrizTraficoDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MatrizTrafico *pp = (MatrizTrafico *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getTrafico(i));
        case 1: return long2string(pp->getCambiado());
        case 2: return long2string(pp->getCalcular());
        default: return "";
    }
}

bool MatrizTraficoDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MatrizTrafico *pp = (MatrizTrafico *)object; (void)pp;
    switch (field) {
        case 0: pp->setTrafico(i,string2double(value)); return true;
        case 1: pp->setCambiado(string2long(value)); return true;
        case 2: pp->setCalcular(string2long(value)); return true;
        default: return false;
    }
}

const char *MatrizTraficoDescriptor::getFieldStructName(int field) const
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

void *MatrizTraficoDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MatrizTrafico *pp = (MatrizTrafico *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


