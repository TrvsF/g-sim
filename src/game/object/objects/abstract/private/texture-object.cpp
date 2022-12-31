#include "../texture-object.h"

namespace object
{
	TextureObject::TextureObject(GameObject* object, const char* textureid)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
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
}