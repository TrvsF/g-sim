#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include "../src/game/object/component/triangle.h"
#include "../src/game/object/game-object.h"
#include "../src/util/maths.h"
#include <vector>

namespace object
{
	class GeometryObject : public GameObject
	{
	private:
		std::vector<Triangle*> m_tris;

		void create_tris(std::vector<Vector2D> points);
	public:
		GeometryObject(GameObject* object, int sides);
		GeometryObject(GameObject* object, std::vector<Vector2D> points);

		inline std::vector<Triangle*> GetTris();
	};
}

#include "geometry-object-inl.h"

#endif