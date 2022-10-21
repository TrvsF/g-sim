#include "../camera.h"

namespace object
{
	Camera::Camera(GameObject* gameobject)
		: GameObject(gameobject)
	{
		m_subject = nullptr;
		m_debug = true;
		m_interp_pos = VEC2_ZERO;
	}

	void Camera::SetSubject(GameObject* gameobject)
	{
		// run some checks?
		m_subject = gameobject;
	}

	void Camera::SetTexturePos(GameObject* gameobject)
	{
		object::TextureObject* object = static_cast<object::TextureObject*> (gameobject);
		object::Texture* textureobj = object->GetTexture();
		Vector2D pos = { 
			object->GetTransform().GetPosition().x - m_offset_pos.x,
			object->GetTransform().GetPosition().y - m_offset_pos.y 
		};

		// if offscreen dont render
		if (pos.x + textureobj->Width() < 0 || pos.x > m_screensize.x || pos.y + textureobj->Height() < 0 || pos.y > m_screensize.y)
		{
			textureobj->Active(false);
			return;
		}

		textureobj->Active(true);
		textureobj->Pos(pos);
	}

	void Camera::Tick()
	{
		if (!m_subject) { return; }

		// follow the player
		Vector3D subject_midpoint = m_subject->GetAABB().GetMidpoint();
		// how much we need to move to follow the player
		Vector3D offsetpos = { 
			(subject_midpoint.x - (GetPosition().x + m_offset_pos.x)) - (GetSize().width / 2),
			(subject_midpoint.y - (GetPosition().y + m_offset_pos.y)) - (GetSize().height / 2),
			(subject_midpoint.z - GetPosition().z) - (GetSize().depth / 2)
		};

		m_screensize = renderer::Renderer::Get()->GetScreensize();

		// where the camera will endup
		AABB newaabb = GetAABB();
		newaabb.OffsetPos(offsetpos);

		// if the in the next frame the camera will be offscreen
		if (   newaabb.GetMinX() < 0 || newaabb.GetMaxX() > m_screensize.x
			|| newaabb.GetMinY() < 0 || newaabb.GetMaxY() > m_screensize.y)
		{
			m_offset_pos += offsetpos;
		}
		else
		{
			GetAABB().OffsetPos(offsetpos);
			GetTransform().OffsetPosition(offsetpos);
		}

		if (m_debug)
		{
			DrawBB();
			printf("%.2f, %.2f\n", m_offset_pos.x, m_offset_pos.y);
		}

	}
}