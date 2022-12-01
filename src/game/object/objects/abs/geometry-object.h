#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include "../src/game/object/component/geometry.h"
#include "../src/game/object/game-object.h"

#include <vector>

namespace object
{
	class GeometryObject : public GameObject
	{
	private:
		Geometry* m_geometry;

		void load_geometry();
	public:
		GeometryObject(GameObject* object, int sides);
		GeometryObject(GameObject* object, std::vector<Vector2D> points);

		inline Geometry* GetGeometry();
	};
}

#include "geometry-object-inl.h"

#endif