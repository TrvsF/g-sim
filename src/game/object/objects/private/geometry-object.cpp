#include "../geometry-object.h"

namespace object
{
	void GeometryObject::setup()
	{
		// load into the renderer
		if (m_debug) { renderer::Renderer::SharedInstace().LoadAABB(&GetAABB()); }
		renderer::Renderer::SharedInstace().LoadGeometry(m_geometry);
		// set type
		SetObjType(GameObjectType::Geometry);
		// create geometry object
		m_geometry = new Geometry();
	}

	GeometryObject::GeometryObject(GameObject* object, int sides)
		: GameObject(object)
	{
		setup();

		float width =  GetAABB().GetMaxX() - GetAABB().GetMinX();
		float height = GetAABB().GetMaxY() - GetAABB().GetMinY();
		Vector2D mins, maxes;
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y},
			sides,
			width,
			height,
			mins,
			maxes
		);
		GetAABB().SetSize({ width, height, 0 });
		GetAABB().SetPos({ GetPosition().x + mins.x, GetPosition().y + mins.y, 0 }); // TODO : rarely doesnt work as indended
	}

	GeometryObject::GeometryObject(GameObject* object, std::vector<Vector2D> points)
		: GameObject(object)
	{
		setup();

		m_geometry->Set(
			{ GetPosition().x, GetPosition().y },
			points
		);
	}

	GeometryObject::~GeometryObject()
	{
		if (m_debug) { renderer::Renderer::SharedInstace().UnloadAABB(&GetAABB()); }
		renderer::Renderer::SharedInstace().UnloadGeometry(GetGeometry());
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