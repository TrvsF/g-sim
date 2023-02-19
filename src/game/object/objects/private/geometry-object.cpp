#include "../geometry-object.h"

namespace object
{
	void GeometryObject::loadgeometry()
	{
		renderer::Renderer::SharedInstace().LoadGeometry(m_geometry);
		if (m_debug) { renderer::Renderer::SharedInstace().LoadAABB(&GetAABB()); }
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
		loadgeometry();
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
		loadgeometry();
	}

	GeometryObject::~GeometryObject()
	{
		if (m_debug) { renderer::Renderer::SharedInstace().UnloadAABB(&GetAABB()); }
		if (m_debug) { renderer::Renderer::SharedInstace().UnloadGeometry(GetGeometry()); }
	}

	void GeometryObject::HandleOffsets()
	{
		GetTransform().OffsetPosition(m_offset_pos);
		GetAABB().OffsetPos(m_offset_pos);

		GetTransform().OffsetRotation(m_offset_rotation);
		m_geometry->OffsetRotation(m_offset_rotation.z);
	}

	void GeometryObject::SetPosition(Vector2D pos)
	{
		GetTransform().SetPosition({ pos.x, pos.y, 0 });
		GetAABB().SetPos({ pos.x, pos.y, 0 });
	}

	void GeometryObject::SetRotation(float rotation)
	{
		GetTransform().SetRotation({ 0, 0, rotation });
		m_geometry->Rotation(rotation);
	}

	void GeometryObject::Update()
	{
	}
}