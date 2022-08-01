#include "../game-object.h"

namespace object
{
	GameObject::GameObject(Object* object, const char* textureid)
	{
		m_object	= object;
		m_velocity	= 0;
		set_texture_from_id(textureid);
		reset_movement_bools();
	}

	void GameObject::Tick()
	{
		handle_movement();
		handle_position();
		// last
		reset_movement_bools();
	}
	
	void GameObject::set_texture_from_id(const char* id)
	{
		m_texture = new Texture();
		SDL_Texture* t = renderer::Renderer::Get()->GetSetTextureFromId(id, m_texture);
		m_texture->Set(t, { 
			m_object->GetPosition().x,
			m_object->GetPosition().y 
			}, m_object->GetTransform().GetRotation().z
		);
	}

	void GameObject::handle_movement()
	{
		if (Forward)
		{
			m_velocity++;
		}

		if (Backward)
		{
			m_velocity--;
		}
	}

	void GameObject::handle_position()
	{
		// calculate new offset for the pos vector
		float yaw = m_object->GetTransform().GetRotation().z;
		Vector2D direction_vec2d = { (float)cosf(yaw), (float)sin(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_velocity;

		m_texture->OffsetPos(pos_change_vec2d);
		m_object->GetAABB().OffsetOrigin({ pos_change_vec2d.x, pos_change_vec2d.y, 0 } );
		m_object->GetTransform().OffsetPosition({ pos_change_vec2d.x, pos_change_vec2d.y, 0 });
	}

	void GameObject::reset_movement_bools()
	{
		Forward		= false;
		Backward	= false;
		Left		= false;
		Right		= false;
	}
}