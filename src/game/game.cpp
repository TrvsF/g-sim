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
		object::GameObject* obj = object::GameObject::Create(
			{  0.0f,  0.0f,  0.0f  },
			{  0.0f,  0.0f,  0.0f  }, 
			{ 32.0f, 32.0f,  32.0f }
		);

		m_player = new object::TextureObject(obj, "player");
		m_game_objects.push_back(m_player);

		object::GameObject* obj2 = object::GameObject::Create(
			{ 300.0f, 20.0f, 0.0f },
			{ 0.0f,   0.0f,   0.0f },
			{ 300.0f, 300.0f, 300.0f }
		);

		m_camera = new object::Camera(obj2);
		m_game_objects.push_back(m_camera);

		// TODO : FIGURE OUT HOW THE BB IS SETUP/RENDERING <<< ITS RENDERING BOTTOM RIGHT??!?!??
	}

	void Game::Tick()
	{
		m_player->Tick();
		m_camera->Tick();

		printf("IS INTER : %d\n", m_camera->GetAABB().IntersectsRect2D(m_player->GetAABB()));
	}
}