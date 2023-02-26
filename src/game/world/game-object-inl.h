#include "game-object.h"

namespace object
{
	inline GameObject* GameObject::Create(Vector3D position, Vector3D rotation, Size size)
	{
		return new GameObject(AABB::Create(position, size), Transform::Create(position, rotation));
	}

	inline Transform& GameObject::GetTransform()
	{
		return m_transform;
	}

	inline void GameObject::SetTransform(Transform& transform)
	{
		m_transform = transform;
	}

	inline AABB& GameObject::GetAABB()
	{
		return m_aabb;
	}

	inline void GameObject::SetAABB(AABB& aabb)
	{
		m_aabb = aabb;
	}

	inline const Vector2D GameObject::Get2DPosition() const
	{
		return { m_transform.GetPosition().x, m_transform.GetPosition().y };
	}

	inline const Vector3D GameObject::GetPosition() const
	{
		return m_transform.GetPosition();
	}

	inline void GameObject::SetPosition(Vector3D position)
	{
		m_transform.SetPosition(position);
		m_aabb.SetPos(position);
	}

	inline const Size GameObject::GetSize() const
	{
		return m_aabb.GetSize();
	}

	inline void GameObject::SetSize(Size size)
	{
		m_aabb.SetSize(size);
	}

	inline const GameObjectType GameObject::GetObjType() const
	{
		return m_object_type;
	}

	inline void GameObject::SetObjType(GameObjectType type)
	{
		m_object_type = type;
	}

	inline const GameEntityType GameObject::GetEntityType() const
	{
		return m_entity_type;
	}

	inline void GameObject::SetEntityType(GameEntityType type)
	{
		m_entity_type = type;
	}
}