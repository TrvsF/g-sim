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

	inline const Vector3D GameObject::GetPosition() const
	{
		return m_transform.GetPosition();
	}

	inline void GameObject::SetPosition(Vector3D position)
	{
		m_transform.SetPosition(position);
	}

	inline const Size GameObject::GetSize() const
	{
		return m_aabb.GetSize();
	}

	inline void GameObject::SetSize(Size size)
	{
		m_aabb.SetSize(size);
	}

	inline void GameObject::DrawBB()
	{
		SDL_Rect rect;
		rect.w = (int)m_aabb.GetMaxX() - (int)m_aabb.GetMinX();
		rect.h = (int)m_aabb.GetMaxY() - (int)m_aabb.GetMinY();
		rect.x = (int)m_aabb.GetMinX();
		rect.y = (int)m_aabb.GetMinY();

		Vector3D pos = m_transform.GetPosition();

		// printf("w %d h %d x %d y %d\n", rect.w, rect.h, rect.x, rect.y);
		// printf("x %.2f y %.2f z %.2f\n", pos.x, pos.y, pos.z);

		renderer::Renderer::Get()->AddTempShape(rect);
	}
}