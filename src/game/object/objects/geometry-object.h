#ifndef GEOMETRYOBJECT_H_
#define GEOMETRYOBJECT_H_

#include "../src/game/object/component/geometry.h"
#include "../src/game/object/game-object.h"
#include "../src/renderer/renderer.h"
#include "../src/event/event.h"

#include <vector>

namespace object
{
	inline std::shared_ptr<_EventBus> bus = event::Event::SharedInstace().EventBus;
	class GeometryObject : public GameObject
	{
	private:
		Geometry* m_geometry;

		void setup();
	public:
		GeometryObject(GameObject* object, int sides);
		GeometryObject(GameObject* object, std::vector<Vector2D> points);
		~GeometryObject();

		void SetRotation(float rotation);
		void SetPosition(Vector2D position);

		void HandleOffsets();
		void Update();

		inline Geometry* GetGeometry();
	};
}

#include "geometry-object-inl.h"

#endif