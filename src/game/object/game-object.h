#ifndef OBJECT_H_
#define OBJECT_H_

#include "component/aabb.h"
#include "component/transform.h"

// debug includes
#include <iostream>
#include "../src/renderer/renderer.h"
#include "SDL.h"

namespace object
{
	class GameObject
	{
	protected:
		bool		m_debug;
		Vector3D	m_offset_pos;
		Vector3D	m_offset_rotation;
	private:
		AABB		m_aabb;
		Transform	m_transform;

	public:
		GameObject(AABB aabb, Transform transform)
			: m_aabb(aabb), m_transform(transform), m_debug(false)
		{}
		GameObject(GameObject* gameobject)
			: m_aabb(gameobject->GetAABB()), m_transform(gameobject->GetTransform())
		{}

		inline static GameObject* Create(Vector3D position, Vector3D rotation, Size size);

		inline Transform& GetTransform();
		inline void SetTransform(Transform& transform);

		inline AABB& GetAABB();
		inline void SetAABB(AABB& aabb);

		inline const Vector3D GetPosition() const;
		inline void SetPosition(Vector3D position);

		inline const Size GetSize() const;
		inline void SetSize(Size size);

		inline GameObject* GetObject();

		// tick runs for every game object, update is used for children to be overwritten
		virtual void Update()
		{}
		
		void Tick()
		{
			m_offset_pos = VEC3_ZERO;
			m_offset_rotation = VEC3_ZERO;

			Update();

			m_aabb.OffsetPos(m_offset_pos);
			m_transform.OffsetRotation(m_offset_rotation);
			m_transform.OffsetPosition(m_offset_pos);

			if (m_debug)
			{
				renderer::Renderer::Get()->LoadAABB(&m_aabb);
			}
		}
	};
}

#include "game-object-inl.h"

#endif