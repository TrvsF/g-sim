#ifndef _BIOME_OBJECT_H
#define _BIOME_OBJECT_H

#include "../src/game/world/component/geometry.h"
#include "../src/game/world/game-object.h"
#include "../src/renderer/renderer.h"
#include "../src/util/vector2d.h"

namespace object
{
	class BiomeObject : public GameObject
	{
	private:
		Geometry* m_geometry;
	public:
		BiomeOjbect(BiomeObject* object, Vector2D size);

		GetBiomeFromPos(Vector2D pos);
	};
}

#endif