#ifndef TILEOBJ_HPP
#define TILEOBJ_HPP

#include "memory.hpp"

class TileObj : public ObjBase
{
public:
    TileObj();

    // Does this object interrupt line of sight? Default: false
    virtual bool DoesBreakLOS();
    // Can this object be passed through? Default: false
    virtual bool DoesBlockPathing();
    // Draw the object to these pixel coordinates
    virtual void Draw(float fX, float fY, double dTime) = 0;
};
typedef ObjPointer<TileObj> PTileObj;

#endif // TILEOBJ_HPP
