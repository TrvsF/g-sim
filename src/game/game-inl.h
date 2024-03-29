#include "game.h"

namespace game
{
	inline void Game::AddGameObject(object::GameObject* gameobject)
	{
		m_collision->AddCollisionObj(gameobject);
		m_gameobjects.push_back(gameobject);

		// if (gameobject->GetEntityType() == object::GameEntityType::Agent)
		// {
		// 	const auto& agent = dynamic_cast<object::Agent*>(gameobject);
		// 	console::bus->postpone(event::eAgentSpawn { agent });
		// 	console::bus->process();
		// }
	}

	inline void Game::RemoveGameObject(object::GameObject* gameobject)
	{
		// remove from gameworldobjects
		auto it = std::find(m_gameobjects.begin(), m_gameobjects.end(), gameobject);
		if (it != m_gameobjects.end()) { m_gameobjects.erase(it); }
		// if already exists 
		it = std::find(m_toremove.begin(), m_toremove.end(), gameobject);
		if (it != m_toremove.end()) { return; }
		m_collision->RemoveCollisionObj(gameobject);
		// delete gameobject;
		m_toremove.push_back(gameobject);
	}

	inline void Game::SetPlayer(object::Player* player)
	{
		m_player = player;
	}

	inline const std::vector<object::GameObject*> Game::GetGameObjects() const
	{
		return m_gameobjects;
	}

	inline object::Player* Game::GetPlayer()
	{
		return m_player;
	}
}