#include "../texture-object.h"

namespace object
{
	TextureObject::TextureObject(GameObject* object, const char* textureid)
		: GameObject(object)
	{
		set_texture_from_id(textureid);
		m_debug = true;
	}

	void TextureObject::set_texture_from_id(const char* id)
	{
		m_texture = new Texture();
		SDL_Texture* texture = renderer::Renderer::Get()->GetSetTextureObjFromId(id, m_texture);
		m_texture->Set(
			texture,
			{
				GetPosition().x,
				GetPosition().y
			}, 
			GetTransform().GetRotation().z
		);
	}

	void TextureObject::Update()
	{
		float yaw = GetTransform().GetRotation().z;
		Vector2D direction_vec2d = { (float)cosf(yaw), (float)sin(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * 2;

		m_offset_pos = { pos_change_vec2d.x, pos_change_vec2d.y, 0.0f };

		m_texture->OffsetPos(pos_change_vec2d);
	}
	
}