#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <type_traits>
#include <unordered_map>
#include "common.hpp"

class ObjBase
{
public:
    ObjBase();
    virtual~ObjBase();
};


typedef std::unordered_map<ObjBase *, ulong> ObjectMap;
namespace Memory
{
    void AddObject(ObjBase *ptObj);
    void RemoveObject(ObjBase *ptObj);

    ulong AddRef(ObjBase *ptObj);
    ulong DecRef(ObjBase *ptObj);

    void ReleaseAllObjects();
    ObjectMap &GetGlobalObjectMap();
}


template<class T>
class ObjPointer
{
    static_assert(std::is_base_of<ObjBase, T>::value, "Cannot generate pointer to object that does not inherit from ObjBase");

public:
    ObjPointer():
        m_ptPointer(NULL)
    {}

    ObjPointer(const ObjPointer &crpOther):
        m_ptPointer(crpOther.m_ptPointer)
    {
        Memory::AddRef(static_cast<ObjBase*>(m_ptPointer));
    }

    virtual ~ObjPointer()
    {
        Release();
    }

    void Release()
    {
        if (NULL != m_ptPointer)
        {
            ulong ulRefCount = Memory::DecRef(static_cast<ObjBase*>(m_ptPointer));

            if (0 == ulRefCount)
            {
                delete m_ptPointer;
            }
        }

        m_ptPointer = NULL;
    }

    ObjPointer &operator=(T *ptObj)
    {
        Release(); // In case we are pointing to something, now we longer point to it

        m_ptPointer = ptObj;
        Memory::AddRef(static_cast<ObjBase*>(m_ptPointer));

        return *this;
    }

    ObjPointer &operator=(const ObjPointer &crpOther)
    {
        (*this) = crpOther.m_ptPointer;
    }

    // Allow our inner pointer to be used transparently
    T &operator*()
    {
        return *m_ptPointer;
    }
    const T &operator*() const
    {
        return *m_ptPointer;
    }
    T *operator->()
    {
        return m_ptPointer;
    }
    const T *operator->() const
    {
        return m_ptPointer;
    }

private:
    T *m_ptPointer;
};

#endif // MEMORY_HPP
