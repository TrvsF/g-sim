#include "../text-object.h"

namespace object
{
	TextObject::TextObject(GameObject* object, const char* font, std::string text, SDL_Color colour)
		: GameObject(object)
	{
		SetObjType(GameObjectType::Texture);
		set_text(font, text, colour);
		m_debug = false;
	}

	void TextObject::set_text(const char* font, std::string text, SDL_Color colour)
	{
		m_texture = new Texture();
		m_font = font;
		m_text = text;
		m_colour = colour;

		SDL_Texture* texture = renderer::Renderer::SharedInstace().GetSetTextureObjFromText(m_font, m_text, m_colour, m_texture);
		m_texture->Set(
			texture,
			{
				GetPosition().x,
				GetPosition().y
			},
			GetTransform().GetRotation().z
		);
	}

	void TextObject::update_text()
	{
		// free the old text
		SDL_DestroyTexture(m_texture->GetTexture());
		// set the new one
		SDL_Texture* texture = renderer::Renderer::SharedInstace().GetSetTextureObjFromText(m_font, m_text, m_colour, nullptr);
		m_texture->Set(texture);
	}

	void TextObject::SetText(std::string text)
	{
		m_text = text;
		update_text();
	}

	void TextObject::SetColour(SDL_Color colour)
	{
		m_colour = colour;
		update_text();
	}

	void TextObject::HandleOffsets()
	{
		GetTransform().OffsetPosition(m_offset_pos);
		GetAABB().OffsetPos(m_offset_pos);

		GetTransform().OffsetRotation(m_offset_rotation);
		m_texture->OffsetRotation(m_offset_rotation.z);
	}

	void TextObject::Update()
	{
		
	}
}