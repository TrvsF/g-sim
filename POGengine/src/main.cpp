#include <iostream>
#include "engine/engine.h"

#undef main

int main()
{
    if (engine::Init())
    {
        engine::Run();
    }
    std::cin.get();
    return 0;
}