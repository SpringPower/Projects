#include <algorithm>
#include "memory.hpp"

ObjectMap g_atObjects;

ObjectMap::iterator GetObj(ObjBase *ptObj)
{
    auto objiter = g_atObjects.find(ptObj);
    EXPECT_TRUE(g_atObjects.end() != objiter);

    return objiter;
}

void Memory::AddObject(ObjBase *ptObj)
{
    std::pair<ObjectMap::iterator, bool> result = g_atObjects.insert(ObjectMap::value_type(ptObj, 0));
    EXPECT_TRUE(result.second);
}

ulong Memory::AddRef(ObjBase *ptObj)
{
    auto objiter = GetObj(ptObj);

    objiter->second++;
    return objiter->second;
}

ulong Memory::DecRef(ObjBase *ptObj)
{
    auto objiter = GetObj(ptObj);

    EXPECT_TRUE(0 < objiter->second);

    objiter->second--;
    return objiter->second;
}


void Memory::RemoveObject(ObjBase *ptObj)
{
    auto objiter = GetObj(ptObj);
    EXPECT(0, objiter->second);

    g_atObjects.erase(objiter);
}


ObjBase::ObjBase()
{
    Memory::AddObject(this);
}

ObjBase::~ObjBase()
{
    Memory::RemoveObject(this);
}


ObjectMap &Memory::GetGlobalObjectMap()
{
    return g_atObjects;
}


void Memory::ReleaseAllObjects()
{
    for (ObjectMap::iterator iter = g_atObjects.begin(); iter != g_atObjects.end(); ++iter)
    {
        delete iter->first;
    }
}
