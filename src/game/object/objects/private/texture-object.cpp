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
		SDL_Texture* texture = renderer::Renderer::SharedInstace().GetSetTextureObjFromId(id, m_texture);
		m_texture->Set(
			texture,
			{
				GetPosition().x,
				GetPosition().y
			}, 
			GetTransform().GetRotation().z
		);
	}

	void TextureObject::HandleOffsets()
	{
		GetTransform().OffsetPosition(m_offset_pos);
		GetAABB().OffsetPos(m_offset_pos);

		GetTransform().OffsetRotation(m_offset_rotation);
		m_texture->OffsetRotation(m_offset_rotation.z);
	}

	void TextureObject::Update()
	{

	}
}