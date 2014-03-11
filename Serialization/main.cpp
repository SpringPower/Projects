#include <iostream>
#include <vector>
#include "serialization.hpp"


using namespace std;

class IntInt: public Serialization::Serializeable<int, int>
{
public:
    IntInt(){}
    virtual~IntInt(){}

    NAME_TYPE(0, one);
    NAME_TYPE(1, two);
};

class CharIntInt: public Serialization::Serializeable<char, IntInt>
{
public:
    CharIntInt(){}
    virtual~CharIntInt(){}

    NAME_TYPE(0, character);
    NAME_TYPE(1, intint);
};

int main()
{
    IntInt tTest;
    CharIntInt tCharInt;
    Serialization::Serializeable<std::vector<int> >tThing2;

    tTest.one = 9;
    tTest.two = 10;
    tCharInt.character = 9;
    tCharInt.intint.one = 10;
    tCharInt.intint.two = 11;

    std::get<0>(tThing2.m_tTuple).push_back(9);
    std::get<0>(tThing2.m_tTuple).push_back(10);

    Serialization::Buffer tBuff;

    //tTest.Serialize(tBuff);
    //tCharInt.Serialize(tBuff);
    tThing2.Serialize(tBuff);

    for(auto e: tBuff)
    {
        cout << (int)e << endl;
    }

    return 0;
}

