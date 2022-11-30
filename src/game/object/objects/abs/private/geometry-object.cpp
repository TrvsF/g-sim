#include "../geometry-object.h"

namespace object
{
	void GeometryObject::set_geometry()
	{
		renderer::Renderer::Get()->LoadGeometry(m_geometry);
	}

	GeometryObject::GeometryObject(GameObject* object, int sides)
		: GameObject(object)
	{
		m_geometry = new Geometry();
		set_geometry(); // sometimes causes a crash??!?!???
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y},
			sides,
			GetAABB().GetMaxX() - GetAABB().GetMinX(),
			GetAABB().GetMaxY() - GetAABB().GetMinY()
		);
	}

	GeometryObject::GeometryObject(GameObject* object, std::vector<Vector2D> points)
		: GameObject(object)
	{
		m_geometry = new Geometry();
		set_geometry();
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y },
			points
		);
	}
}