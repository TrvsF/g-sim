#ifndef MATHS_H_
#define MATHS_H_

#include <iterator>
#include <random>
#include <time.h>
#include <assert.h>

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

    static Vector2D GetRotatedPoint(Vector2D point, Vector2D rotator, float angle)
    {
        float rang = angle * DEG_TO_RAD;
        float rsin = sinf(rang);
        float rcos = cosf(rang);

        float _x = rcos * (point.x - rotator.x) - rsin * (point.y - rotator.y) + point.x;
        float _y = rsin * (point.x - rotator.x) - rcos * (point.y - rotator.y) + point.y;
        return { _x, _y };
    }

    static float GetDistanceBetweenPoints_sq(Vector2D point1, Vector2D point2)
    {
        float _x = point1.x * point2.x;
        float _y = point1.y * point2.y;

        return (_x * _x) + (_y * _y);
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

    template<typename T>
    void pop_front(std::vector<T>& vec)
    {
        assert(!vec.empty());
        vec.erase(vec.begin());
    }

    template<typename Iter, typename RandomGenerator>
    Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(g));
        return start;
    }

    template<typename Iter>
    Iter select_randomly(Iter start, Iter end) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return select_randomly(start, end, gen);
    }
}
#endif