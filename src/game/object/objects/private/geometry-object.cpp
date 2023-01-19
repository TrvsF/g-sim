#include "../geometry-object.h"

namespace object
{
	void GeometryObject::load_geometry()
	{
		renderer::Renderer::Get()->LoadGeometry(m_geometry);
	}

	GeometryObject::GeometryObject(GameObject* object, int sides)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Geometry);
		m_geometry = new Geometry();
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y},
			sides,
			GetAABB().GetMaxX() - GetAABB().GetMinX(),
			GetAABB().GetMaxY() - GetAABB().GetMinY()
		);
		load_geometry();
	}

	GeometryObject::GeometryObject(GameObject* object, std::vector<Vector2D> points)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Geometry);
		m_geometry = new Geometry();
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y },
			points
		);
		load_geometry();
	}

	void GeometryObject::HandleOffsets()
	{
		GetTransform().OffsetPosition(m_offset_pos);
		GetAABB().OffsetPos(m_offset_pos);

		GetTransform().OffsetRotation(m_offset_rotation);
		m_geometry->OffsetRotation(m_offset_rotation.z);
	}

	void GeometryObject::Update()
	{
	}
}