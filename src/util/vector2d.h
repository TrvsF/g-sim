#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#define PI 3.14159265f
#define DEG_TO_RAD PI / 180.0f

#include <math.h>

struct Vector2D
{
	float x;
	float y;

	Vector2D(float _x = 0, float _y = 0)
		: x(_x), y(_y)
	{}

	Vector2D(Vector2D const &v)
		: x(v.x), y(v.y)
	{}

	float magnitudeSqr()
	{
		return x * x + y * y;
	}

	float magnitude()
	{
		return (float)sqrt(x * x + y * y);
	}

	Vector2D normalised()
	{
		float mag = magnitude();
		return Vector2D(x / mag, y / mag);
	}

	Vector2D& operator +=(const Vector2D& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2D& operator -=(const Vector2D& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2D operator -() const
	{
		return Vector2D(-x, -y);
	}
};

inline bool operator == (const Vector2D& lhs, const Vector2D& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2D operator * (const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.x * rhs.x, lhs.y * rhs.y);
}

inline Vector2D operator * (const Vector2D& lhs, const float& rhs) {

	return Vector2D(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2D operator / (const Vector2D& lhs, const float& rhs) {

	return Vector2D(lhs.x / rhs, lhs.y / rhs);
}

inline Vector2D operator / (const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.x / rhs.x, lhs.y / rhs.y);
}

inline Vector2D RotateVector(Vector2D& vec, float angle)
{
	float radAngle = (float)angle * DEG_TO_RAD;
	return Vector2D((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

const Vector2D VEC2_ZERO	= { 0, 0 };
const Vector2D VEC2_ONE		= { 1, 1 };
const Vector2D VEC2_UP		= { 0, 1 };
const Vector2D VEC2_RIGHT	= { 1, 0 };

#endif // !VECTOR2D_H_