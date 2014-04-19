#include <iostream>
#include "common.hpp"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    try
    {
        EXPECT_TRUE(5 == 9);
    }
    catch (std::exception *e)
    {
        LOG(e->what());
    }

    return 0;
}

