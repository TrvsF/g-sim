#include "game.h"

namespace game
{
	inline Game* Game::Get()
	{
		return Game::s_instance;
	}

	inline void Game::AddGameObject(object::GameObject* game_object)
	{
		add_collision_element(game_object);
		m_gameworld_objects.push_back(game_object);
	}

	inline void Game::SetPlayer(object::Player* player)
	{
		m_player = player;
	}

	inline const std::vector<object::GameObject*> Game::GetGameObjects() const
	{
		return m_gameworld_objects;
	}

	inline object::Player* Game::GetPlayer()
	{
		return m_player;
	}
}