#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include "common.hpp"
#include <tuple>

class ISerializeable
{
public:
    ISerializeable(){};
    virtual ~ISerializeable(){};

    virtual size_t Serialize(char *pcBuffStart, size_t cbBuffSize) = 0;
};

template <class T>
struct Serializer
{
    std::enable_if<std::is_pod<T>::value, bool>
    static size_t Serialize(const T &crtObj, char *pcBuffStart, size_t cbBuffSize)
    {
        size_t cbItemSize = Serialize<TUPLE>(std::get<i>(tTup));
        Serialize<TUPLE, i-1>(tTup, pcBuffStart + cbItemSize, cbBuffSize - cbItemSize);
    }
};

template <class TUPLE, int i>
struct Serializer
{
    static size_t Serialize(const TUPLE &tTup, char *pcBuffStart, size_t cbBuffSize)
    {
        size_t cbItemSize = Serialize<TUPLE>(std::get<i>(tTup), pcBuffStart, cbBuffSize);
        Serialize<TUPLE, i-1>(tTup, pcBuffStart + cbItemSize, cbBuffSize - cbItemSize);
    }
};

template <class TUPLE>
struct Serializer<-1>
{
    static size_t Serialize(const TUPLE &tTup, char *pcBuffStart, size_t cbBuffSize)
    {
        (void)tTup;
    }
};

#endif // SERIALIZATION_HPP
