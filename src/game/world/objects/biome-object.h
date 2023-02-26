#ifndef _BIOME_OBJECT_H
#define _BIOME_OBJECT_H

#include "../src/game/world/component/geometry.h"
#include "../src/game/world/game-object.h"
#include "../src/renderer/renderer.h"
#include "../src/util/vector2d.h"

namespace object
{
	enum class BiomeType
	{
		Desert,
		Aquatic,
		Grassland,
		Forest,
		Tundra
	};

	class BiomeObject : public Geometry
	{
	private:
		Geometry* m_geometry;
	public:
		BiomeObject(Vector2D size);
		~BiomeObject();

		BiomeType GetBiomeFromPos(Vector2D pos);
	};
}

#endif