#include "../collision.h"

namespace game
{
	Collision::Collision(int scale)
	{
		m_gridscale = scale;
	}

	bool Collision::is_colliding(object::GameObject* obj1, object::GameObject* obj2)
	{
		return obj1->GetAABB().IntersectsRect2D(obj2->GetAABB());
	}

	// -1 for infinite range
	bool Collision::is_looking(object::GameObject* searcher, object::GameObject* gameobject, int fov, int range)
	{
		bool inrange = range == -1 ? true : maths::GetDistanceBetweenPoints_sq(searcher->Get2DPosition(), gameobject->Get2DPosition()) < range * range;
		return maths::IsInConeOfVision
		(
			searcher->GetTransform().Get2DPosition(),
			gameobject->GetTransform().Get2DPosition(),
			fov,
			searcher->GetTransform().GetRotation().z
		) && inrange;
	}

	void Collision::check_agent(object::Agent* agent)
	{
	}

	// TODO : (((somehow))) cut down on the nested fors
	void Collision::DoCollision()
	{
		// first  = grid pos pair
		// second = list of objs in grid
		for (auto& mapobj : m_mapped_objects)
		{
			int x = mapobj.first.first;
			int y = mapobj.first.second;
			auto& currentgridobjs = mapobj.second;
			// check each surrounding grid tile
			for (auto& gridpair : get_surroundinggridpairs(std::pair<int, int>(x, y), true))
			{
				// if grid does not exist in map
				if (m_mapped_objects.find(gridpair) == m_mapped_objects.end()) { continue; }
				// store searched grid objects
				auto& searchedobjs = m_mapped_objects[gridpair];
				for (auto& gridobj : currentgridobjs)
				{
					for (auto& searchedobj : searchedobjs)
					{
						// if looping over self/null
						if (searchedobj == gridobj || searchedobj == nullptr || gridobj == nullptr) { continue; }

						// TODO : move this block
						// if obj is an agent
						if (gridobj->GetEntityType() == object::GameEntityType::Agent)
						{
							// if gridobject is looking @ searchedobject
							if (searchedobj->GetEntityType() == object::GameEntityType::Agent && is_looking(gridobj, searchedobj, 120, -1))
							{
								object::Agent* agent  = static_cast<object::Agent*> (gridobj);
								object::Agent* victim = static_cast<object::Agent*> (searchedobj);
								if (!victim->IsDead()) { agent->SeenEnt(victim); }
							}
							// if gridobject is colliding with searchedobject
							if (is_colliding(gridobj, searchedobj))
							{
								// TODO : this can push a garbage pointer (for 1 tick)
								object::Agent* agent = static_cast<object::Agent*> (gridobj);
								agent->AddCollidedObj(searchedobj);
							}
						}

						
					}
				}
			}
		}
	}

	void Collision::CheckCollisionObj(object::GameObject* game_object)
	{
		std::pair<int, int> gridpair = get_gridfromcoords(game_object->GetPosition().x, game_object->GetPosition().y);
		auto& objectlist = m_mapped_objects[gridpair];
		// if object is not in the grid
		if (std::find(objectlist.begin(), objectlist.end(), game_object) == objectlist.end())
		{
			for (auto& newpair : get_surroundinggridpairs(gridpair, false))
			{
				if (m_mapped_objects.find(newpair) == m_mapped_objects.end()) { continue; }
				// if does then remove from old grid
				auto& newlist = m_mapped_objects[newpair];
				newlist.erase(std::remove(newlist.begin(), newlist.end(), game_object), newlist.end());
				if (newlist.empty())
				{
					m_mapped_objects.erase(newpair);
				}
			}
			m_mapped_objects[gridpair].push_back(game_object);
		}
	}

	void Collision::AddCollisionObj(object::GameObject* game_object)
	{
		std::pair<int, int> gridpair = get_gridfromcoords(game_object->GetPosition().x, game_object->GetPosition().y);
		// if does not exist
		if (m_mapped_objects.find(gridpair) == m_mapped_objects.end())
		{
			m_mapped_objects.insert({ gridpair, { game_object } });
		}
		else
		{
			m_mapped_objects[gridpair].push_back(game_object);
		}
	}

	std::vector<std::pair<int, int>> Collision::get_surroundinggridpairs(std::pair<int, int> currentgrid, bool includeown)
	{
		std::vector<std::pair<int, int>> gridpairs;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0 && !includeown) { continue; }
				gridpairs.push_back(std::pair<int, int>(currentgrid.first + i, currentgrid.second + j));
			}
		}
		return gridpairs;
	}

	std::pair<int, int> Collision::get_gridfromcoords(float x, float y)
	{
		int _x = (int)roundf(x / m_gridscale);
		int _y = (int)roundf(y / m_gridscale);

		return std::pair<int, int>(_x, _y);
	}
}