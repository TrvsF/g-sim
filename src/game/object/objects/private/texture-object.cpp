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

	TextureObject::TextureObject(GameObject* object, const char* font, std::string text, SDL_Color colour)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
		set_text(font, text, colour);
		m_debug = false;
	}

	void TextureObject::set_text(const char* font, std::string text, SDL_Color colour)
	{
		m_texture = new Texture();
		SDL_Texture* texture = renderer::Renderer::SharedInstace().GetSetTextureObjFromText("HenryBlue-Regular", "hello georgia!", { 0, 255, 0 }, m_texture);
		m_texture->Set(
			texture,
			{
				GetPosition().x,
				GetPosition().y
			},
			GetTransform().GetRotation().z
		);
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