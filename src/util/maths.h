#ifndef MATHS_H_
#define MATHS_H_

#include <random>
#include <time.h>

namespace maths
{
    static int GetRandomInt(int min, int max)
    {
        return min + (rand() % static_cast<int>(max - min + 1));
    }

    static float GetRandomFloat(float min, float max)
    {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }
}

#endif