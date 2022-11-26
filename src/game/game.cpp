#include "game.h"

namespace game
{
	Game* Game::s_instance = nullptr;

	Game::Game()
	{
		m_player = nullptr;
		m_camera = nullptr;
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

	void Game::Start()
	{
		// SETUP CAMERA AND PLAYER OBJECTS
		object::GameObject* playerobj = object::GameObject::Create(
			{  200.0f,  200.0f,  0.0f  },
			{  0.0f,    0.0f,    0.0f  }, 
			{  32.0f,   32.0f,   32.0f }
		);

		m_player = new object::Player(playerobj, "player");
		m_gameworld_objects.push_back(m_player); // TODO : MAKE SURE THIS IS ALWAYS AT THE FRONT

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
			{ 50.0f,   50.0f,   0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 32.0f,   32.0f,   32.0f }
		);
		m_gameworld_objects.push_back(new object::GeometryObject(triman));
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