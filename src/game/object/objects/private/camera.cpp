#include "../camera.h"

namespace object
{
	Camera::Camera(GameObject* gameobject)
		: GameObject(gameobject)
	{
		m_subject = nullptr;
		m_debug = true;
	}

	void Camera::SetSubject(GameObject* gameobject)
	{
		// run some checks?
		m_subject = gameobject;
	}


	void Camera::InterpTexture(GameObject* gameobject)
	{
		
	}

	void Camera::Update()
	{
		if (!m_subject) { return; }

		// follow the player
		Vector3D subject_midpoint = m_subject->GetAABB().GetMidpoint();
		m_offset_pos = { 
			(subject_midpoint.x - GetPosition().x) - (GetSize().width / 2),
			(subject_midpoint.y - GetPosition().y) - (GetSize().height / 2),
			(subject_midpoint.z - GetPosition().z) - (GetSize().depth / 2)
		};

	}
}