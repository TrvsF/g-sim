#include "../texture-object.h"

namespace object
{
	TextureObject::TextureObject(GameObject* object, const char* textureid)
		: GameObject(object)
	{
		set_texture_from_id(textureid);
	}

	void TextureObject::set_texture_from_id(const char* id)
	{
		m_texture = new Texture();
		SDL_Texture* t = renderer::Renderer::Get()->GetSetTextureFromId(id, m_texture);
		m_texture->Set(t, {
			GetPosition().x,
			GetPosition().y
			}, GetTransform().GetRotation().z
		);
	}
	
}