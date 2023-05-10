#ifndef MATHS_H_
#define MATHS_H_

#include "file.h"

#include <iterator>
#include <random>
#include <time.h>
#include <assert.h>
#include <SDL_pixels.h>

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

    static Vector2D GetRotatedPointBad(Vector2D point, Vector2D rotator, float degrees)
    {
        float rang = degrees * DEG_TO_RAD;
        float rsin = sinf(rang);
        float rcos = cosf(rang);

        float _x = rcos * (point.x - rotator.x) - rsin * (point.y - rotator.y) + point.x;
        float _y = rsin * (point.x - rotator.x) - rcos * (point.y - rotator.y) + point.y;
        return { _x, _y };
    }

    static float GetDistanceBetweenPoints_sq(Vector2D point1, Vector2D point2)
    {
        float _x = point2.x - point1.x;
        float _y = point2.y - point1.y;

        return (_x * _x) + (_y * _y);
    }

    static void GetRotatedPoint(Vector2D& point, Vector2D midpoint, float degrees)
    {
        Vector2D temppoint = VEC2_ZERO;
        float rang = degrees * DEG_TO_RAD;
        float sin = sinf(rang);
        float cos = cosf(rang);

        temppoint.x = point.x - midpoint.x;
        temppoint.y = point.y - midpoint.y;

        float _x = temppoint.x * cos - temppoint.y * sin;
        float _y = temppoint.x * sin + temppoint.y * cos;

        point.x = _x + midpoint.x;
        point.y = _y + midpoint.y;
    }

    static int GetAngleBetweenPoints(Vector2D point1, Vector2D point2)
    {
        int angle = (int)roundf(atan2f(point2.y - point1.y, point2.x - point1.x) * RAD_TO_DEG);
        GetBoundedAngleDeg(angle);

        return angle;
    }

    static bool IsPointInsideOfRadius(Vector2D point, Vector2D circlepoint, int radius)
    {
        int r2 = radius * radius;
        float px2 = (point.x - circlepoint.x) * (point.x - circlepoint.x);
        float py2 = (point.y - circlepoint.y) * (point.y - circlepoint.y);
        return px2 + py2 < r2;
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

    static double ColourDifference(SDL_Color c1, SDL_Color c2)
    {
        long rmean = ((long)c1.r + (long)c2.r) / 2;
        long r = (long)c1.r - (long)c2.r;
        long g = (long)c1.g - (long)c2.g;
        long b = (long)c1.b - (long)c2.b;
        return sqrt((((512 + rmean) * r * r) >> 8) + 4 * g * g + (((767 - rmean) * b * b) >> 8));
    }

    static int StringToDecimal(std::string str, bool twos)
    {
        const int N = str.length();
        char* end;
        int decimal = strtoull(str.c_str(), &end, 2);
        if (decimal & 1 << (N - 1) && twos) decimal |= ~((1 << N) - 1);
        return decimal;
    }

    template <std::ranges::input_range R, typename T>
        requires std::indirect_binary_predicate<std::ranges::equal_to, std::ranges::iterator_t<R>, const T*>
    bool index(R&& range, const T& value) 
    {
        return std::ranges::find(range, value) != std::ranges::end(range);
    }

    template<typename Iter, typename RandomGenerator>
    Iter select_randomly(Iter start, Iter end, RandomGenerator& g) 
    {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(g));
        return start;
    }

    template<typename Iter>
    Iter select_randomly(Iter start, Iter end) 
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return select_randomly(start, end, gen);
    }

    template<typename T>
    struct delete_pointer_element
    {
        void operator()(T element) const
        {
            delete element;
        }
    };

    // TODO : move
    
    
    static std::string get_randomname()
    {
        std::vector<std::string> firstnames = file::GetLinesFromFile("firstnames.txt");
        std::vector<std::string> lastnames = file::GetLinesFromFile("lastnames.txt");
        return *select_randomly(firstnames.begin(), firstnames.end())
            + "." + *select_randomly(lastnames.begin(), lastnames.end());
    }
}
#endif