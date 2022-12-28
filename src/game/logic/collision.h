#ifndef COLLISION_H_
#define COLLISION_H_

#include "../object/game-object.h"

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

		std::vector<std::pair<int, int>> get_surrounding_grid_pairs(std::pair<int, int> currentgrid, bool includeown);
		std::pair<int, int> get_grid_from_coords(float x, float y);
	public:
		Collision(int scale);

		void CheckCollisionObj(object::GameObject* game_object);
		void AddCollisionObj(object::GameObject* game_object);
		void DoCollision();
	};
}

#endif