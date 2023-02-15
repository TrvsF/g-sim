#ifndef MATHS_H_
#define MATHS_H_

#include <random>
#include <time.h>

namespace maths
{
    #define PI 3.14159265f
    #define DEG_TO_RAD PI / 180.0f
    #define RAD_TO_DEG 180.0f / PI

    static int GetRandomInt(int min, int max)
    {
        return min + (rand() % static_cast<int>(max - min + 1));
    }

    static float GetRandomFloat(float min, float max)
    {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }

    static void GetBoundedAngleDeg(int& angle)
    {
        angle = angle % 360;
        if (angle < 0) { angle += 360; }
    }

    static int GetAngleBetweenPoints(Vector2D point1, Vector2D point2)
    {
        int angle = (int)roundf(atan2f(point2.y - point1.y, point2.x - point1.x) * RAD_TO_DEG);
        GetBoundedAngleDeg(angle);

        return angle;
    }

    static bool IsInConeOfVision(Vector2D origin, Vector2D point, int fov, float rotation)
    {
        int ang = GetAngleBetweenPoints(origin, point);
        int pang = (int)roundf(rotation);
        GetBoundedAngleDeg(pang);

        return !(pang - (fov / 2.0f) >= ang || pang + (fov / 2.0f) <= ang);
    }

    static bool IsInRange(Vector2D origin, Vector2D point, int distance)
    {
        float x = (point.x - origin.x) * (point.x - origin.x);
        float y = (point.y - origin.y) * (point.y - origin.y);
        int calcdistance = (int)roundf(sqrtf(x + y));

        return calcdistance <= distance;
    }
}
#endif