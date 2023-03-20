#include "base/engine.h"

#undef main

/*--------
 TODO:
 CAMERA NEEDS A COMPLETE REWORK!
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