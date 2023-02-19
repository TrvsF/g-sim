#ifndef GAME_H_
#define GAME_H_

#include "../base/helper_macos.h"

#include "../base/console.h"

#include "object/game-object.h"
#include "entities/camera.h"
#include "entities/player.h"
#include "entities/agent.h"
#include "entities/food.h"

#include "object/objects/text-object.h"
#include "object/objects/texture-object.h"
#include "object/objects/geometry-object.h"

#include "logic/collision.h"

#include "../src/updater/controller.h"
#include "../event/event.h"

#include <dexode/EventBus.hpp>
using Listener = dexode::EventBus::Listener;

#include <unordered_map>
#include <algorithm>
#include <vector>

namespace game
{
	class Game
	{
	private:
		Game();

		// event objects & methods
		Listener m_listener { event::Event::SharedInstace().EventBus };
		void e_poschange(const event::ePosChange& event);
		void e_agentdeath(const event::eAgentDeath& event);

		std::vector<object::GameObject*> m_toremove;

		// logic objects
		Collision*	m_collision;

		// world object stuff
		std::vector<object::GameObject*> m_gameobjects;
		object::Player* m_player;
		object::Camera* m_camera;

		// TODO : this another way maybe?
		object::TextObject* m_consoletxt;
		object::TextObject* m_coords;
		void doconsole();

		// input stuff (todo: move?)
		object::GameObject* m_selected_obj;
		Vector2D			m_selected_obj_offset;
	public:
		static Game& SharedInstace() { static Game game; return game; }

		void OnMouseRelease(int mousebutton);
		void OnMouseDown(int mousebutton, int x, int y);
		void OnMouseClick(int mousebutton,int x, int y);
		object::GameObject* GetClickedObj(int x, int y);

		inline void AddGameObject(object::GameObject* gameobject);
		inline void RemoveGameObject(object::GameObject* gameobject);
		inline const std::vector<object::GameObject*> GetGameObjects() const;

		inline void SetPlayer(object::Player* player);
		inline object::Player* GetPlayer();

		void Start();
		void Tick();
	};
}

#include "game-inl.h"

#endif