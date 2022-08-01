#include "game.h"

namespace game
{
	Game* Game::s_instance = nullptr;

	Game::Game()
	{
		m_player = nullptr;
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
		object::Object* obj = object::Object::Create(
			{100, 50,  0},
			{  0,  0,  0}, 
			{ 25, 25, 25}
		);

		m_player = new object::GameObject(obj, "player");
		m_game_objects.push_back(m_player);
	}

	void Game::Tick()
	{
		m_player->Tick();
	}
}