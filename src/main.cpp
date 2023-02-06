#include "base/engine.h"

#undef main

/*--------
 TODO:
 [bugs]
 -
 [improvements]
 - 
 [additions]
 -
--------*/

int main(int argc, char* argv[])
{
    if (base::Init())
    {
        base::Run();
    }
    std::cin.get();
    return 0;
}