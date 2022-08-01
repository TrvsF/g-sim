#include "base/engine.h"

#undef main

/*--------
 TODO:
 [bugs]
 -
 [improvements]
 - timers faster
 - 
 [additions]
 -
--------*/

int main()
{
    if (base::Init())
    {
        base::Run();
    }
    std::cin.get();
    return 0;
}