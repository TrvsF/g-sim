#include "../texture.h"

namespace object
{
	Texture::Texture()
		: m_texutre(nullptr), m_pos(VEC2_ZERO), m_rotation(0), m_width(0), m_height(0), m_active(false), m_scale(1), m_type(TextureType::Static)
	{}

	Texture::Texture(SDL_Texture* texture)
		: m_texutre(texture), m_pos(VEC2_ZERO), m_rotation(0), m_width(0), m_height(0), m_active(false), m_scale(1), m_type(TextureType::Static)
	{
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);
	}

	void Texture::Set(SDL_Texture* texture)
	{
		m_texutre = texture;
		m_active = true;
		m_type = TextureType::Static;
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);
	}

	void Texture::Set(SDL_Texture* texture, Vector2D pos, float rotation)
	{
		m_type = TextureType::Static;
		Set(texture);
		m_pos = pos;
	}

	void Texture::Set(SDL_Texture* texture, Vector2D pos, float rotation, int frames, int offset)
	{
		m_type = TextureType::Dynamic;
		m_texutre = texture;
		m_active = true;
		m_pos = pos;
		m_data = { frames, frames, offset };
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);
	}
}
