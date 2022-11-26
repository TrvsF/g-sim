#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include "../src/game/object/component/triangle.h"
#include "../src/game/object/game-object.h"
#include <vector>

namespace object
{
	class GeometryObject : public GameObject
	{
	private:
		std::vector<Triangle> m_tris;

		float m_rotate;
	public:
		GeometryObject(GameObject* object);

		// debug
		std::vector<SDL_Vertex> GetVert();

		inline float Rotate();
		inline void Rotate(float rotate);
	};
}

#include "geometry-object-inl.h"

#endif