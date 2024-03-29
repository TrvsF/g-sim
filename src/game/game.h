#ifndef GAME_H_
#define GAME_H_

#include "../base/helper_macos.h"

#include "../base/console.h"

#include "world/game-object.h"
#include "world/entities/camera.h"
#include "world/entities/player.h"
#include "world/entities/agent.h"
#include "world/entities/food.h"

#include "world/objects/text-object.h"
#include "world/objects/texture-object.h"
#include "world/objects/geometry-object.h"
#include "world/objects/biome-object.h"

#include "logic/collision.h"

#include "ai/god.h"

#include "../src/updater/controller.h"
#include "../event/event.h"

#include <dexode/EventBus.hpp>
using Listener = dexode::EventBus::Listener;

#include <unordered_map>
#include <algorithm>
#include <vector>

namespace game
{
	struct ToBeBorn
	{
		float x;
		float y;
		std::string genus;
		std::string lastname;
	};

	class Game
	{
	private:
		Game();

		// event objects & methods
		Listener m_listener { event::Event::SharedInstace().EventBus };
		void e_poschange(const event::ePosChange& event);
		void e_scalechange(const event::eScaleChange& event);
		void e_objectdeath(const event::eObjectDeath& event);
		void e_agentbirth(const event::eAgentBorn& event);

		// logic objects
		Collision*	m_collision;

		// world object stuff
		std::vector<object::GameObject*> m_toremove;
		std::vector<object::GameObject*> m_gameobjects;
		object::Player* m_player;
		object::Camera* m_camera;
		void spawn_food(int x, int y, int size);
		void spawn_agent(int x, int y, std::string genus, std::string lastname);

		// TODO : bad agent hack
		std::vector<ToBeBorn> m_tobeborn;

		// world gen TODO : move
		// object::BiomeObject* m_biome;
		int m_seed = 0;
		void generate_map();
		void init_entities();
		void init_textelements();

		// zoom
		void zoom(float zoom, Vector2D mousepos);

		// TODO : this another way maybe?
		// URGENT TODO : all text is broke idk why
		object::TextObject* m_consoletxt;
		object::TextObject* m_coords;
		object::TextObject* m_debugname;
		object::Agent*		m_debugfollow;
		void do_textelements();

		// input help TODO : move
		object::GameObject* get_clickedobject(int x, int y);
	public:
		static Game& SharedInstace() { static Game game; return game; }

		// TODO : redesign
		bool R = false;
		bool G = false;
		bool B = false;

		void MouseRelease(int mousebutton);
		void MouseDown (int mousebutton, int x, int y);
		void MouseClick(int mousebutton, int x, int y);
		void ScrollDown(int mousebutton, int x, int y);
		void ScrollUp  (int mousebutton, int x, int y);
		void MoveCamera(Vector2D movevec);

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