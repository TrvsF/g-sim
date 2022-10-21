#ifndef GAME_H_
#define GAME_H_

#include "../base/helper_macos.h"
#include "object/game-object.h"
#include "object/objects/camera.h"
#include "object/objects/player.h"
#include "object/objects/agent.h"
#include "object/objects/abs/texture-object.h"

#include <vector>

namespace game
{
	class Game
	{
	private:
		static Game* s_instance;

		std::vector<object::GameObject*> m_gameworld_objects;

		object::Player* m_player;
		object::Camera* m_camera;
	public:
		Game();

		static void Create();
		static inline Game* Get();
		static void Destroy();

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