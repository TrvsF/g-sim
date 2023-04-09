#include "../geometry-object.h"

namespace object
{
	void GeometryObject::setup()
	{
		// set type
		SetObjType(GameObjectType::Geometry);
		// create geometry object
		m_geometry = new Geometry();
		// load into the renderer
		if (m_debug) { renderer::Renderer::SharedInstace().LoadAABB(&GetAABB()); }
		renderer::Renderer::SharedInstace().LoadGeometry(m_geometry);
	}

	GeometryObject::GeometryObject(GameObject* object, int sides)
		: GameObject(object)
	{
		setup();

		float width =  GetAABB().GetMaxX() - GetAABB().GetMinX();
		float height = GetAABB().GetMaxY() - GetAABB().GetMinY();
		m_geometry->Set(
			{ GetPosition().x, GetPosition().y},
			sides,
			width,
			height
		);
		GetAABB().SetSize({ width, height, 0 });
	}

	GeometryObject::GeometryObject(GameObject* object, std::vector<Vector2D> points)
		: GameObject(object)
	{
		setup();

		m_geometry->Set(
			{ GetPosition().x, GetPosition().y },
			points
		);
		Vector2D size = m_geometry->Size();
		GetAABB().SetSize({ size.x, size.y });
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

	float GeometryObject::GetArea()
	{
		float totalarea = 0;
		for (const auto& tri : m_geometry->Tris())
		{
			float a = tri.GetPoint1().x   * (tri.GetPoint2().y   - tri.GetMidpoint().y);
			float b = tri.GetPoint2().x   * (tri.GetMidpoint().y - tri.GetPoint1().y);
			float c = tri.GetMidpoint().x * (tri.GetPoint1().y   - tri.GetPoint2().y);
			totalarea += fabsf(a + b + c) * 0.5f;
		}
		return totalarea;
	}

	float GeometryObject::GetSpikyness()
	{
		const auto& tris = m_geometry->Tris();
		int tricount = tris.size();
		Vector2D midpoint = tris[0].GetMidpoint();
		float totalangle = 0;

		// get each other point
		for (int i = 0; i < tris.size(); i++)
		{
			Vector2D p1 = tris[i].GetPoint1();
			Vector2D p2 = tris[i].GetPoint2();
			Vector2D p3 = i == tris.size() - 1 ? tris[0].GetPoint1() : tris[i + 1].GetPoint1();

			float a = atan2f(p3.y - p1.y, p3.x - p1.x);
			float b = atan2f(p2.y - p1.y, p2.x - p1.x);
			float ang = a - b;

			totalangle += fabsf(ang);
		}

		return totalangle / tricount;
	}

	void GeometryObject::Update()
	{
	}
}