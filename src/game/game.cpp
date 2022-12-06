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

	void Game::Start()
	{
		// SETUP CAMERA AND PLAYER OBJECTS
		object::GameObject* playerobj = object::GameObject::Create(
			{  200.0f,  200.0f,  0.0f  },
			{  0.0f,    0.0f,    0.0f  }, 
			{  32.0f,   32.0f,   32.0f }
		);

		m_player = new object::Player(playerobj, "player");
		m_gameworld_objects.push_back(m_player); // TODO : MAKE SURE THIS IS ALWAYS AT THE FRONT (z indexing?)

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
		m_gameworld_objects.push_back(new object::Agent(miscagent, "player"));

		object::GameObject* triman = object::GameObject::Create(
			{ 150.0f,   0.0f,   0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 232.0f,   232.0f,   232.0f }
		);
		object::GameObject* triman2 = object::GameObject::Create(
			{ -50.0f,   -50.0f,   0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 232.0f,   232.0f,   232.0f }
		);
		object::GameObject* triman3 = object::GameObject::Create(
			{ 250.0f,   250.0f,   0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 232.0f,   232.0f,   232.0f }
		);
		object::GameObject* triman4 = object::GameObject::Create(
			{ 50.0f,   50.0f,   0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 232.0f,   232.0f,   232.0f }
		);
		srand(time(NULL)); // move me
		m_gameworld_objects.push_back(new object::GeometryObject(triman, 4));
		m_gameworld_objects.push_back(new object::GeometryObject(triman2, 5));
		m_gameworld_objects.push_back(new object::GeometryObject(triman3, 4));
		m_gameworld_objects.push_back(new object::GeometryObject(triman4, 5));
	}

	// entities -> camera
	void Game::Tick()
	{
		for (object::GameObject* gameworldobject : m_gameworld_objects)
		{
			gameworldobject->Tick();
		}
		m_camera->Tick();
		for (object::GameObject* gameworldobject : m_gameworld_objects)
		{
			m_camera->SetTexturePos(gameworldobject);
		}
	}
}