#ifndef OBJECT_H_
#define OBJECT_H_

#include "component/aabb.h"
#include "component/transform.h"
#include "../src/util/vector2d.h"
// debug includes
#include <iostream>
#include "SDL.h"

namespace object
{
	enum class GameObjectType
	{
		Texture,
		Geometry,
		None
	};

	enum class GameEntityType
	{
		Player,
		Food,
		Agent,
		None
	};

	class GameObject
	{
	protected:
		bool		m_debug;
		Vector3D	m_offset_pos;
		Vector3D	m_offset_rotation;
	private:
		GameObjectType	m_object_type;
		GameEntityType  m_entity_type;
		AABB			m_aabb; 
		Transform		m_transform;
		// todo this is bad
		bool m_setup = false;

	public:
		GameObject(AABB aabb, Transform transform)
			: m_aabb(aabb), m_transform(transform), m_debug(false), m_object_type(GameObjectType::None), m_entity_type(GameEntityType::None)
		{}
		GameObject(GameObject* gameobject)
			: m_aabb(gameobject->GetAABB()), m_transform(gameobject->GetTransform())
		{}
		virtual ~GameObject() = default;

		inline static GameObject* Create(Vector3D position, Vector3D rotation, Size size);

		inline Transform& GetTransform();
		inline void SetTransform(Transform& transform);

		inline AABB& GetAABB();
		inline void SetAABB(AABB& aabb);

		inline const Vector2D Get2DPosition() const;
		inline const Vector3D GetPosition() const;
		inline void SetPosition(Vector3D position);

		inline const Size GetSize() const;
		inline void SetSize(Size size);

		inline const GameObjectType GetObjType() const;
		inline void SetObjType(GameObjectType type);

		inline const GameEntityType GetEntityType() const;
		inline void SetEntityType(GameEntityType type);

		virtual void HandleOffsets()
		{}

		// tick runs for every game object, update is used for children to be overwritten
		virtual void Update()
		{}
		
		// update pos of object
		void Tick()
		{
			m_offset_pos = VEC3_ZERO;
			m_offset_rotation = VEC3_ZERO;

			Update();
			HandleOffsets();

			// rebug render where game object is
			if (m_debug)
			{
				if (!m_setup)
				{
					// renderer::Renderer::SharedInstace().LoadAABB(&m_aabb);
					m_setup = true;
				}
				/*
				// show rotation
				float r = GetTransform().GetRotation().z;
				int x = GetPosition().x;
				int y = GetPosition().y;
				int x2 = x + (cosf(r) * 20);
				int y2 = y + (sinf(r) * 20);
				SDL_RenderDrawLine(renderer::Renderer::Get()->GetRendererObj(), x, y, x2, y2);
				*/
			}
		}
	};
}

#include "game-object-inl.h"

#endif