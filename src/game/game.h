#ifndef GAME_H_
#define GAME_H_

#include "../base/helper_macos.h"

#include "object/game-object.h"
#include "entities/camera.h"
#include "entities/player.h"
#include "entities/agent.h"
#include "entities/food.h"
#include "object/objects/texture-object.h"
#include "object/objects/geometry-object.h"

#include "logic/level.h"
#include "logic/collision.h"

#include "../src/updater/controller.h"

#include <unordered_map>
#include <algorithm>
#include <vector>

namespace game
{
	class Game
	{
	private:
		Game();

		// logic objects
		Collision*	m_collision;
		Level*		m_level;

		// world object stuff
		std::vector<object::GameObject*> m_gameworld_objects;
		object::Player* m_player;
		object::Camera* m_camera;

		// input stuff (todo: move?)
		object::GameObject* m_selected_obj;
		Vector2D			m_selected_obj_offset;
	public:
		static Game& SharedInstace() { static Game game; return game; }

		void OnMouseRelease(int mousebutton);
		void OnMouseClick(int x, int y, int mousebutton);
		object::GameObject* GetClickedObj(int x, int y);

		inline void AddGameObject(object::GameObject* game_object);
		inline const std::vector<object::GameObject*> GetGameObjects() const;

		inline void SetPlayer(object::Player* player);
		inline object::Player* GetPlayer();

		void Start();
		void Tick();
	};
}

#include "game-inl.h"

#endif