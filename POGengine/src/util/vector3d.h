#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#define PI 3.14159265f
#define DEG_TO_RAD PI / 180.0f

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D& operator +=(const Vector3D& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vector3D(float _x = 0, float _y = 0, float _z = 0)
		: x(_x), y(_y), z(_z)
	{}
};

inline Vector3D operator + (const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline Vector3D operator - (const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z + rhs.z);
}

inline Vector3D operator * (const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

inline Vector3D operator * (const Vector3D& lhs, const float& rhs) {

	return Vector3D(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

inline Vector3D operator / (const Vector3D& lhs, const Vector3D& rhs)
{
	return Vector3D(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

inline Vector3D operator / (const Vector3D& lhs, const float& rhs) {

	return Vector3D(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

const Vector3D VEC3_ZERO	= { 0, 0, 0 };
const Vector3D VEC3_UNIT	= { 1, 1, 1 };
const Vector3D VEC3_UNIT_X	= { 1, 0, 0 };
const Vector3D VEC3_UNIT_Y	= { 0, 1, 0 };
const Vector3D VEC3_UNIT_Z	= { 0, 0, 1 };

#endif // !VECTOR3D_H_