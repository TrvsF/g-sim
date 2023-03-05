#include "../texture-object.h"

namespace object
{
	TextureObject::TextureObject(GameObject* object, const char* textureid)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
		set_texture_from_id(textureid, 1, 0);
		m_debug = true;
	}

	TextureObject::TextureObject(GameObject* object, const char* textureid, int frames, int offset)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
		set_texture_from_id(textureid, frames, offset);
		m_debug = true;
	}

	void TextureObject::set_texture_from_id(const char* id, int frames, int offset)
	{
		m_texture = new Texture();
		SDL_Texture* texture = renderer::Renderer::SharedInstace().GetSetTextureObjFromId(id, m_texture);
		if (frames == 1)
		{
			m_texture->Set(
				texture,
				{
					GetPosition().x,
					GetPosition().y
				},
				GetTransform().GetRotation().z
			);
		}
		else
		{
			m_texture->Set(
				texture,
				{
					GetPosition().x,
					GetPosition().y
				},
				GetTransform().GetRotation().z,
				frames,
				offset
			);
		}
		
		
		if (m_debug) { renderer::Renderer::SharedInstace().LoadAABB(&GetAABB()); }
	}

	TextureObject::~TextureObject()
	{
		renderer::Renderer::SharedInstace().UnloadTexture(GetTexture());
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