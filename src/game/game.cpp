#include "game.h"

namespace game
{
	Game* Game::s_instance = nullptr;

	Game::Game()
	{
		m_player = nullptr;
		m_camera = nullptr;

		m_selected_obj = nullptr;
	}

	void Game::Create()
	{
		if (!Game::s_instance)
		{
			Game::s_instance = new Game();
		}
	}

	void Game::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	void Game::OnMouseRelease()
	{
		m_selected_obj = nullptr;
	}

	void Game::OnMouseClick(int x, int y)
	{
		// if there is no selected object see if we can find one
		if (m_selected_obj == nullptr)
		{
			bool found = false;
			for (object::GameObject* object : m_gameworld_objects)
			{
				// TODO : Change to texture
				if (object->GetAABB().IntersectsPoint(x, y))
				{
					m_selected_obj = object;
					m_selected_obj_offset = { x - object->GetPosition().x, y - object->GetPosition().y };
					found = true;
					break;
				}
			}
			if (!found) { return; }
		}
		// move the about around :D
		Vector3D pos = { x - m_selected_obj_offset.x, y - m_selected_obj_offset.y, 0 };
		m_selected_obj->SetPosition(pos);
	}

	void Game::DoCollision()
	{
		// TODO : make this not look shit
		for (auto& it : m_mapped_objects) 
		{
			int x = it.first.first;
			int y = it.first.second;
			auto& const currentgridobjs = it.second;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					std::pair<int, int> newpair(x + i, y + j);
					if (m_mapped_objects.find(newpair) == m_mapped_objects.end()) { continue; }
					// if does then remove from old grid
					auto& const newlist = m_mapped_objects[newpair];
					for (auto& const oldobj : currentgridobjs)
					{
						for (auto& const newobj : newlist)
						{
							if (newobj == oldobj) { continue; }
							if (oldobj->GetAABB().IntersectsRect2D(newobj->GetAABB()))
							{
								std::cout << "c";
							}
						}
					}
				}
			}
		}
	}

	void Game::check_collision_element(object::GameObject* game_object)
	{
		int gridscale = 128;
		int x = (int)roundf(game_object->GetPosition().x / gridscale);
		int y = (int)roundf(game_object->GetPosition().y / gridscale);

		std::pair<int, int> pair(x, y);
		auto& const objectlist = m_mapped_objects[pair];

		// if object is not in the grid
		if (std::find(objectlist.begin(), objectlist.end(), game_object) == objectlist.end())
		{
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					// if doesnt exist there continue
					if (i == 0 && j == 0) { continue; }
					std::pair<int, int> newpair(x + i, y + j);
					if (m_mapped_objects.find(newpair) == m_mapped_objects.end()) { continue; }
					// if does then remove from old grid
					auto& const newlist = m_mapped_objects[newpair];
					newlist.erase(std::remove(newlist.begin(), newlist.end(), game_object), newlist.end());
					if (newlist.empty())
					{
						m_mapped_objects.erase(newpair);
					}
				}
			}
			m_mapped_objects[pair].push_back(game_object);
		}
	}

	void Game::add_collision_element(object::GameObject* game_object)
	{
		int gridscale = 128;
		int x = (int)roundf(game_object->GetPosition().x / gridscale);
		int y = (int)roundf(game_object->GetPosition().y / gridscale);

		std::pair<int, int> pair(x, y);

		// if does not exist
		if (m_mapped_objects.find(pair) == m_mapped_objects.end())
		{
			m_mapped_objects.insert({ pair, { game_object } });
		}
		else
		{
			m_mapped_objects[pair].push_back(game_object);
		}
	}

	void Game::Start()
	{
		// SETUP CAMERA AND PLAYER OBJECTS
		object::GameObject* playerobj = object::GameObject::Create(
			{  200.0f,  200.0f,  0.0f  },
			{  0.0f,    0.0f,    0.0f  }, 
			{  32.0f,   32.0f,   32.0f }
		);

		m_player = new object::Player(playerobj, "player");
		AddGameObject(m_player);
		// m_gameworld_objects.push_back(m_player); // TODO : MAKE SURE THIS IS ALWAYS AT THE FRONT (z indexing?)

		object::GameObject* cameraobj = object::GameObject::Create(
			{ 0.0f,   0.0f,   0.0f },
			{ 0.0f,   0.0f,   0.0f },
			{ 300.0f, 300.0f, 300.0f }
		);

		m_camera = new object::Camera(cameraobj);
		m_camera->SetSubject(m_player);

		// debug
		object::GameObject* miscagent = object::GameObject::Create(
			{ 100.0f,  400.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 32.0f,   32.0f,   32.0f }
		);
		AddGameObject(new object::Agent(miscagent, 4)); // TODO : Scale BB with tri size

		object::GameObject* food = object::GameObject::Create(
			{ 1000.0f,  400.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 64.0f,   64.0f,   64.0f }
		);
		AddGameObject(new object::Food(food, "food"));

		object::GameObject* triman = object::GameObject::Create(
			{ 150.0f,   0.0f,    0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::GameObject* triman2 = object::GameObject::Create(
			{ 400.0f,   400.0f,  0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::GameObject* triman3 = object::GameObject::Create(
			{ 250.0f,   250.0f,  0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::GameObject* triman4 = object::GameObject::Create(
			{ 50.0f,   50.0f,   0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 64.0f,   64.0f,   64.0f }
		);
		srand(time(NULL)); // move me
		AddGameObject(new object::GeometryObject(triman,  4));
		AddGameObject(new object::GeometryObject(triman2, 5));
		AddGameObject(new object::GeometryObject(triman3, 4));
		AddGameObject(new object::GeometryObject(triman4, 5));
	}

	// entities -> camera
	void Game::Tick()
	{
		for (object::GameObject* gameworldobject : m_gameworld_objects)
		{
			check_collision_element(gameworldobject);
			gameworldobject->Tick();
			DoCollision();
		}
		m_camera->Tick();
		for (object::GameObject* gameworldobject : m_gameworld_objects)
		{
			m_camera->SetTexturePos(gameworldobject);
		}
	}
}