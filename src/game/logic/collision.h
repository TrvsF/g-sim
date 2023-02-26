#ifndef COLLISION_H_
#define COLLISION_H_

#include "../world/game-object.h"
#include "../world/entities/food.h"
#include "../world/entities/agent.h"
#include "../src/util/maths.h"

#include <unordered_map>
#include <algorithm>
#include <vector>

namespace game
{
	struct pairhash {
	public:
		template <typename T, typename U>
		std::size_t operator()(const std::pair<T, U>& x) const
		{
			return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
		}
	};

	class Collision
	{
	private:
		int m_gridscale;

		std::unordered_map<std::pair<int, int>, std::vector<object::GameObject*>, pairhash> m_mapped_objects;

		std::vector<std::pair<int, int>> get_surroundinggridpairs(std::pair<int, int> currentgrid, bool includeown);
		std::pair<int, int> get_gridfromcoords(float x, float y);

		void check_agentcollision(object::Agent* agent, object::Agent* victim);
		bool is_colliding(object::GameObject* obj1, object::GameObject* obj2);
		bool is_looking(object::GameObject* searcher, object::GameObject* gameobject, int fov, int range);
	public:
		Collision(int scale);

		void CheckCollisionObj(object::GameObject* game_object);
		void AddCollisionObj(object::GameObject* game_object);
		void DoCollision();
	};
}

#endif