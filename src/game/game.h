#ifndef GAME_H_
#define GAME_H_

#include "../base/helper_macos.h"
#include "object/game-object.h"
#include "object/objects/entities/camera.h"
#include "object/objects/entities/player.h"
#include "object/objects/entities/agent.h"
#include "object/objects/entities/food.h"
#include "object/objects/abstract/texture-object.h"
#include "object/objects/abstract/geometry-object.h"

#include <unordered_map>
#include <algorithm>
#include <vector>

namespace game
{
	struct pairhash {
	public:
		template <typename T, typename U>
		std::size_t operator()(const std::pair<T, U>& x) const
		{
			return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
		}
	};

	class Game
	{
	private:
		static Game* s_instance;

		// world object stuff
		std::vector<object::GameObject*> m_gameworld_objects;
		object::Player* m_player;
		object::Camera* m_camera;

		// collision stuff (todo: move)
		std::unordered_map<std::pair<int, int>, std::vector<object::GameObject*>, pairhash> m_mapped_objects;
		void check_collision_element(object::GameObject* game_object);
		void add_obj_to_cmap(object::GameObject* game_object);

		// input stuff (todo: move?)
		object::GameObject* m_selected_obj;
		Vector2D			m_selected_obj_offset;
	public:
		Game();

		static void Create();
		static inline Game* Get();
		static void Destroy();

		void OnMouseRelease();
		void OnMouseClick(int x, int y);

		void DoCollision();

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