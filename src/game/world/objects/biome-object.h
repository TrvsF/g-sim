#ifndef BIOME_OBJECT_H_
#define BIOME_OBJECT_H_

#include "../src/game/world/component/geometry.h"
#include "../src/game/world/game-object.h"
#include "../src/renderer/renderer.h"
#include "../src/util/vector2d.h"

#include <vector>

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
		std::vector<std::pair<GameObject*, BiomeType>> m_objectbiomepairs;
		
		float m_width;
		float m_height;
		Geometry* m_geometry;

		std::vector<Vector2D> getpoints();
	public:
		BiomeObject(Vector2D size);
		~BiomeObject();

		BiomeType GetBiomeFromPos(Vector2D pos);
	};
}
#endif