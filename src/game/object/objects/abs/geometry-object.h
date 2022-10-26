#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include "../src/game/object/game-object.h"

namespace object
{
	class GeometryObject : public GameObject
	{
	private:
		float m_rotate;
		float m_side1;
		float m_side2;
	public:
		GeometryObject(GameObject* object);
		GeometryObject(GameObject* object, float rotate, float side1, float side2);

		inline Vector2D Sides();
		inline void Sides(Vector2D sides);
		inline float Rotate();
		inline void Rotate(float rotate);
	};
}

#include "geometry-object-inl.h"

#endif