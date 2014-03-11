#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include "../Descencion/common.hpp"
#include <tuple>
#include <type_traits>
#include <list>

namespace Serialization
{

typedef std::list<unsigned char> Buffer;

class ISerializeable
{
public:
    ISerializeable(){}
    virtual~ISerializeable(){}

    virtual void Serialize(Buffer &atBuffer) const = 0;
    virtual size_t Size() const = 0;
    virtual void Deserialize(Buffer &atBuffer) = 0;
};

template <class T>
typename std::enable_if<std::is_fundamental<T>::value, void>::type
SerializeT(const T &tObj, Buffer &atBuffer)
{
    const unsigned char *ptObj = (reinterpret_cast<unsigned char*>(tObj));

    for (size_t i=0; i<sizeof(T); ++i)
    {
        atBuffer.push_back(*(ptObj+i));
    }
}

template <class T>
typename std::enable_if<std::is_base_of<ISerializeable, T>::value, void>::type
SerializeT(const T &tObj, Buffer &atBuffer)
{
    tObj.Serialize(atBuffer);
}

template <class T>
typename std::enable_if<(!std::is_base_of<ISerializeable, T>::value) && (!std::is_fundamental<T>::value), void>::type
SerializeT(const T &tObj, Buffer &atBuffer)
{
    size_t nElements = tObj.size();

    SerializeT(nElements, atBuffer);

    for (size_t i=0; i<nElements; ++i)
    {
        SerializeT(tObj[i], atBuffer);
    }
}

template <class T>
typename std::enable_if<std::is_fundamental<T>::value, void>::type
DeserializeT(T &tObj, Buffer &atBuffer)
{
    for (size_t i=0; i<sizeof(T); ++i)
    {
        (*(reinterpret_cast<unsigned char*>(tObj)+i)) = atBuffer.front();
        atBuffer.pop_front();
    }
}

template <class T>
typename std::enable_if<std::is_base_of<ISerializeable, T>::value, void>::type
DeserializeT(T &tObj, Buffer &atBuffer)
{
    return tObj.Deserialize(atBuffer);
}

template <class T>
typename std::enable_if<(!std::is_base_of<ISerializeable, T>::value) && (!std::is_fundamental<T>::value), void>::type
DeserializeT(T &tObj, Buffer &atBuffer)
{
    size_t nElements = 0;

    DeserializeT(nElements, atBuffer);

    for (size_t i=0; i<nElements; ++i)
    {
        DeserializeT(tObj[i], atBuffer);
    }
}

template <class T>
typename std::enable_if<std::is_fundamental<T>::value, size_t>::type
SizeT(const T& tObj)
{
    UNREFERNCED_PARAMETER(tObj);
    return sizeof(T);
}

template <class T>
typename std::enable_if<std::is_base_of<ISerializeable, T>::value, size_t>::type
SizeT(const T& tObj)
{
    return tObj.Size();
}

template <class T>
typename std::enable_if<(!std::is_base_of<ISerializeable, T>::value) && (!std::is_fundamental<T>::value), size_t>::type
SizeT(const T& tObj)
{
    size_t nElements = tObj.size();
    size_t cbSize = SizeT(nElements);

    for (size_t i=0; i<nElements; ++i)
    {
        cbSize += SizeT(tObj[i]);
    }

    return cbSize;
}

template <class TUPLE, int i>
struct Serializer
{
    static void Serialize(const TUPLE &tTup, Buffer &atBuffer)
    {
        Serialization::Serializer<TUPLE, i-1>::Serialize(tTup, atBuffer);
        Serialization::SerializeT(std::get<i>(tTup), atBuffer);
    }

    static void Deserialize(TUPLE &tTup, Buffer &atBuffer)
    {
        Serializer<TUPLE, i-1>::Deserialize(tTup, atBuffer);
        Serialization::DeserializeT(std::get<i>(tTup), atBuffer);
    }

    static size_t Size(const TUPLE &tTup)
    {
        return Serialization::SizeT<typename std::tuple_element<i, TUPLE>::type>(std::get<i>(tTup)) +
                Serializer<TUPLE, i-1>::Size(tTup);
    }
};

template <class TUPLE>
struct Serializer <TUPLE, -1>
{
    static void Serialize(const TUPLE &tTup, Buffer &atBuffer)
    {
        UNREFERNCED_PARAMETER(tTup);
        UNREFERNCED_PARAMETER(atBuffer);
    }

    static size_t Deserialize(TUPLE &tTup, Buffer &atBuffer)
    {
        UNREFERNCED_PARAMETER(tTup);
        UNREFERNCED_PARAMETER(atBuffer);

        return 0;
    }

    static size_t Size(const TUPLE &tTup)
    {
        UNREFERNCED_PARAMETER(tTup);

        return 0;
    }
};

template <class ...Args>
class Serializeable: public ISerializeable
{
public:
    Serializeable(){}
    virtual~Serializeable(){}

    virtual void Serialize(Buffer &atBuffer) const
    {
        Serializer<TupleType, std::tuple_size<TupleType>::value-1>::Serialize(m_tTuple, atBuffer);
    }

    virtual size_t Size() const
    {
        return Serializer<TupleType, std::tuple_size<TupleType>::value-1>::Size(m_tTuple);
    }

    virtual void Deserialize(Buffer &atBuffer)
    {
        Serializer<TupleType, std::tuple_size<TupleType>::value-1>::Deserialize(m_tTuple, atBuffer);
    }

//protected:
    typedef std::tuple<Args...> TupleType;
    TupleType m_tTuple;
};
#define NAME_TYPE(index, name)  \
typename std::tuple_element<index, decltype(m_tTuple)>::type &name = std::get<index>(m_tTuple);

}

#endif // SERIALIZATION_HPP
