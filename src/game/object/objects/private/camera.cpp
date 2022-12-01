#include "../camera.h"

namespace object
{
	Camera::Camera(GameObject* gameobject)
		: GameObject(gameobject)
	{
		m_subject = nullptr;
		m_debug = true;
		m_local_offset_pos = VEC3_ZERO;
	}

	void Camera::SetSubject(GameObject* gameobject)
	{
		// todo run some checks?
		m_subject = gameobject;
	}

	void Camera::SetTexturePos(GameObject* gameobject)
	{
		if (gameobject->GetType() == GameObjectType::Texture)
		{
			// if is a texture game object get its texture companant
			object::TextureObject* object = static_cast<object::TextureObject*> (gameobject);
			object::Texture* textureobj = object->GetTexture();
			// get new pos relative to camera object
			Vector2D pos = {
				object->GetTransform().GetPosition().x - m_local_offset_pos.x,
				object->GetTransform().GetPosition().y - m_local_offset_pos.y
			};
			// if offscreen dont render
			if (pos.x + textureobj->Width() < 0 || pos.x > m_screensize.x || pos.y + textureobj->Height() < 0 || pos.y > m_screensize.y)
			{
				textureobj->Active(false);
				return;
			}
			// if onscreen set some values
			textureobj->Active(true);
			textureobj->Pos(pos);
		}
		if (gameobject->GetType() == GameObjectType::Geometry)
		{
			// if is a texture game object get its texture companant
			object::GeometryObject* object = static_cast<object::GeometryObject*> (gameobject);
			object::Geometry* geometry = object->GetGeometry();
			// get new pos relative to camera object
			Vector2D pos = {
				object->GetTransform().GetPosition().x - m_local_offset_pos.x,
				object->GetTransform().GetPosition().y - m_local_offset_pos.y
			};
			// if offscreen dont render
			if (pos.x + object->GetSize().width < 0 || pos.x > m_screensize.x || pos.y + object->GetSize().height < 0 || pos.y > m_screensize.y)
			{
				geometry->Active(false);
				return;
			}
			// if onscreen set some values
			geometry->Active(true);
			geometry->Pos(pos);
		}
	}

	void Camera::Update()
	{
		if (!m_subject) { return; }

		// follow the player
		Vector3D subject_midpoint = m_subject->GetAABB().GetMidpoint();
		// how much we need to move to follow the player
		Vector3D offsetpos = { 
			(subject_midpoint.x - (GetPosition().x + m_local_offset_pos.x)) - (GetSize().width / 2),
			(subject_midpoint.y - (GetPosition().y + m_local_offset_pos.y)) - (GetSize().height / 2),
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
			m_local_offset_pos += offsetpos;
		}
		else
		{
			GetAABB().OffsetPos(offsetpos);
			GetTransform().OffsetPosition(offsetpos);
		}
	}
}