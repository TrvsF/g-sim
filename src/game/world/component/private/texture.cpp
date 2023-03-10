#include "../texture.h"

namespace object
{
	Texture::Texture()
		: m_texture(nullptr), m_pos(VEC2_ZERO), m_rotation(0), m_width(0), m_height(0), m_active(false), m_scale(1), m_type(TextureType::Static), m_xcurrentframe(0), m_ycurrentframe(0)
	{}

	Texture::Texture(SDL_Texture* texture)
		: m_texture(texture), m_pos(VEC2_ZERO), m_rotation(0), m_width(0), m_height(0), m_active(false), m_scale(1), m_type(TextureType::Static), m_xcurrentframe(0), m_ycurrentframe(0)
	{
		SDL_QueryTexture(m_texture, NULL, NULL, &m_twidth, &m_theight);
	}

	void Texture::Set(SDL_Texture* texture)
	{
		m_texture = texture;
		m_active = true;

		SDL_QueryTexture(m_texture, NULL, NULL, &m_twidth, &m_theight);
	}

	void Texture::SetStatic(SDL_Texture* texture, Vector2D pos, float rotation, int width, int height)
	{
		m_type = TextureType::Static;
		Set(texture);

		m_pos = pos;
		m_width = width;
		m_height = height;
	}

	void Texture::SetAnimated(SDL_Texture* texture, Vector2D pos, float rotation, int frames, int width, int height)
	{
		m_type = TextureType::Dynamic;
		Set(texture);

		m_data = { frames, frames };
		m_pos = pos;
		m_width = width;
		m_height = height;
	}

	void Texture::SetText(SDL_Texture* texture, Vector2D pos, float rotation, int width, int height)
	{
		m_type = TextureType::Text;
		Set(texture);

		m_pos = pos;
		m_width = width;
		m_height = height;
	}
}
