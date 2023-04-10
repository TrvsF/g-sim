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
		float distancesq = maths::GetDistanceBetweenPoints_sq(searcher->Get2DPosition(), gameobject->Get2DPosition());
		bool inrange = range == -1 ? true : distancesq < range * range;
		return maths::IsInConeOfVision
		(
			searcher->GetTransform().Get2DPosition(),
			gameobject->GetTransform().Get2DPosition(),
			fov,
			searcher->GetTransform().GetRotation()
		) && inrange;
	}

	void Collision::check_agentcollision(object::Agent* agent, object::Agent* victim)
	{
		if (victim->IsDead() || agent->IsDead()) { return; }
		// if gridobject is looking @ searchedobject
		if (is_looking(agent, victim, 120, 30))
		{
			if (!victim->IsDead()) { agent->SeenEnt(victim); }
		}
		// if gridobject is colliding with searchedobject
		if (is_colliding(agent, victim))
		{
			// TODO : this can push a garbage pointer (for 1 tick)
			agent->AddCollidedObj(victim);
		}
	}

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
						// TODO : check for worldborder
						// if looping over self/null
						if (searchedobj == gridobj || searchedobj == nullptr || gridobj == nullptr) { continue; }

						if (gridobj->GetEntityType() == object::GameEntityType::Agent)
						{
							// cast & check current obj
							object::Agent* agent = static_cast<object::Agent*>(gridobj);
							if (agent->IsDead())
							{ return; }

							// TODO : both distance values set by trait
							int distance = 1000;
							if (searchedobj->GetEntityType() == object::GameEntityType::Agent)
							{
								if (static_cast<object::Agent*>(searchedobj)->IsDead())
								{ return; }
								distance = 50;
							}

							if (is_looking(agent, searchedobj, 120, distance))
							{ agent->SeenEnt(searchedobj); }

							if (is_colliding(agent, searchedobj))
							{ agent->AddCollidedObj(searchedobj); }
						}
					}
				}
			}
		}
	}

	void Collision::RemoveCollisionObj(object::GameObject* game_object)
	{
		std::pair<int, int> gridpair = get_gridfromcoords(game_object->GetPosition().x, game_object->GetPosition().y);
		auto& listofgridobjs = m_mapped_objects[gridpair];
		listofgridobjs.erase(std::remove(listofgridobjs.begin(), listofgridobjs.end(), game_object), listofgridobjs.end());
		if (listofgridobjs.empty())
		{
			m_mapped_objects.erase(gridpair);
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