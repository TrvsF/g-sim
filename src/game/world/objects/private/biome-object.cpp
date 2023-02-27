#include "../biome-object.h"

namespace object
{
	std::vector<Vector2D> BiomeObject::getpoints()
	{
		srand(0);
		std::vector<Vector2D> points;

		return points;
	}

	BiomeObject::BiomeObject(Vector2D size)
	{
		// vars
		Vector2D pos = Vector2D{ -size.x / 2, -size.y / 2 };
		std::vector<Vector2D> points = getpoints();
		// set points

		m_geometry = new Geometry();
		m_geometry->Set(
			pos, points, size.y, size.x
		);
	}

	BiomeObject::~BiomeObject()
	{

	}

	BiomeType BiomeObject::GetBiomeFromPos(Vector2D pos)
	{
		return BiomeType();
	}
}