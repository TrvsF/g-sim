#include "../biome-object.h"

namespace object
{
	std::vector<Vector2D> BiomeObject::getpoints()
	{
		float maxx = m_width / 2.0f;
		float maxy = m_height / 2.0f;
		std::vector<Vector2D> points
		{
			{maxx, maxy},
			{maxx, -maxy},
			{-maxx, maxy},
			{-maxx, -maxy}
		};

		return points;
	}

	BiomeObject::BiomeObject(Vector2D size)
	{
		// set vars
		m_width  = size.x;
		m_height = size.y;
		// get points
		Vector2D pos = Vector2D{ -m_width / 2.0f, -m_height / 2.0f };
		std::vector<Vector2D> points = getpoints();
		// set points
		m_geometry = new Geometry();
		m_geometry->Set(
			pos, points, m_height, m_width
		);
		m_geometry->Colour({ 255, 0, 0 });
		m_geometry->Active(true);
		renderer::Renderer::SharedInstace().LoadGeometry(m_geometry);
	}

	BiomeObject::~BiomeObject()
	{

	}

	BiomeType BiomeObject::GetBiomeFromPos(Vector2D pos)
	{
		return BiomeType();
	}
}