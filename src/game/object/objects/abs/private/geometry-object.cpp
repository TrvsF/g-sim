#include "../geometry-object.h"

namespace object
{
	GeometryObject::GeometryObject(GameObject* object, int sides)
		: GameObject(object)
	{
		m_geometry = new Geometry();
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y},
			sides,
			GetAABB().GetMaxX() - GetAABB().GetMinX(),
			GetAABB().GetMaxY() - GetAABB().GetMinY()
		);
		renderer::Renderer::Get()->LoadGeometry(m_geometry);
	}

	GeometryObject::GeometryObject(GameObject* object, std::vector<Vector2D> points)
		: GameObject(object)
	{
		m_geometry = new Geometry();
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y },
			points
		);
		renderer::Renderer::Get()->LoadGeometry(m_geometry);
	}
}