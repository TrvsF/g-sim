#include "../texture-object.h"

namespace object
{
	TextureObject::TextureObject(Object* object, const char* textureid)
		: GameObject(object)
	{
		set_texture_from_id(textureid);
	}

	void TextureObject::set_texture_from_id(const char* id)
	{
		m_texture = new Texture();
		SDL_Texture* t = renderer::Renderer::Get()->GetSetTextureFromId(id, m_texture);
		m_texture->Set(t, {
			m_object->GetPosition().x,
			m_object->GetPosition().y
			}, m_object->GetTransform().GetRotation().z
		);
	}
	
}