#include "../collision.h"

namespace game
{
	Collision::Collision(int scale)
	{
		m_gridscale = scale;
	}

	void Collision::DoCollision()
	{
		// TODO : make this not look shit
		for (auto& it : m_mapped_objects)
		{
			int x = it.first.first;
			int y = it.first.second;
			auto& currentgridobjs = it.second;
			for (auto& newpair : get_surrounding_grid_pairs(std::pair<int, int>(x, y), true))
			{
				if (m_mapped_objects.find(newpair) == m_mapped_objects.end()) { continue; }
				// if there are items in grid
				auto& newlist = m_mapped_objects[newpair];
				// TODO : store pairs to cut time (in this loop) in 1/2 & run alg on both instead
				for (auto& oldobj : currentgridobjs)
				{
					for (auto& newobj : newlist)
					{
						// if looping over self
						if (newobj == oldobj) { continue; }
						// debug
						if (newobj->GetEntityType() == object::GameEntityType::Agent && oldobj->GetObjType() == object::GameObjectType::Geometry)
						{ 
							bool isobjseen = maths::IsInConeOfVision
							(
								newobj->GetTransform().Get2DPosition(),
								oldobj->GetTransform().Get2DPosition(),
								90,
								newobj->GetTransform().GetRotation().z
							);

							if (isobjseen)
							{
								object::Agent* agent = static_cast<object::Agent*> (newobj);
								agent->SeenEnt(static_cast<object::GeometryObject*> (oldobj));
							}
								
							/*
							std::cout << 
							maths::GetAngleBetweenPoints(
								newobj->GetTransform().Get2DPosition(),
								oldobj->GetTransform().Get2DPosition()
							) << "\n";
							*/
						}
						// if they intersect
						if (oldobj->GetAABB().IntersectsRect2D(newobj->GetAABB()))
						{
							if (oldobj->GetEntityType() == object::GameEntityType::Food)
							{
								object::Food* object = static_cast<object::Food*> (oldobj);
								object->SetCollision(newobj->GetEntityType());
							}
						}
					}
				}
			}
		}
	}

	void Collision::CheckCollisionObj(object::GameObject* game_object)
	{
		std::pair<int, int> gridpair = get_grid_from_coords(game_object->GetPosition().x, game_object->GetPosition().y);
		auto& objectlist = m_mapped_objects[gridpair];
		// if object is not in the grid
		if (std::find(objectlist.begin(), objectlist.end(), game_object) == objectlist.end())
		{
			for (auto& newpair : get_surrounding_grid_pairs(gridpair, false))
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
		std::pair<int, int> gridpair = get_grid_from_coords(game_object->GetPosition().x, game_object->GetPosition().y);
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

	std::vector<std::pair<int, int>> Collision::get_surrounding_grid_pairs(std::pair<int, int> currentgrid, bool includeown)
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

	std::pair<int, int> Collision::get_grid_from_coords(float x, float y)
	{
		int _x = (int)roundf(x / m_gridscale);
		int _y = (int)roundf(y / m_gridscale);

		return std::pair<int, int>(_x, _y);
	}
}