#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

#include "memory.hpp"

class GameObj : public BaseObj
{
public:
    GameObj();

    virtual Logic(double dLength) = 0;
    virtual Draw(double dLength) = 0;
};


#endif // GAMEOBJ_HPP
