#include <iostream>
#include "base/engine.h"

#undef main

int main()
{
    if (base::Init())
    {
        base::Run();
    }
    std::cin.get();
    return 0;
}