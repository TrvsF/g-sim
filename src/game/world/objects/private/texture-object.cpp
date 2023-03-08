#include "../texture-object.h"

namespace object
{
	TextureObject::TextureObject(GameObject* object, const char* textureid)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
		set_texture_from_id(textureid, 1);
		m_debug = true;
	}

	TextureObject::TextureObject(GameObject* object, const char* textureid, int frames)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
		set_texture_from_id(textureid, frames);
		m_debug = true;
	}

	void TextureObject::set_texture_from_id(const char* id, int frames)
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
				GetTransform().GetRotation().z,
				GetAABB().GetMaxX() - GetAABB().GetMinX(),
				GetAABB().GetMaxY() - GetAABB().GetMinY()
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
				GetAABB().GetMaxX() - GetAABB().GetMinX(),
				GetAABB().GetMaxY() - GetAABB().GetMinY()
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