#include "../texture.h"

namespace object
{
	Texture::Texture()
		: m_texutre(nullptr), m_pos(VEC2_ZERO), m_rotation(0), m_width(0), m_height(0), m_active(false)
	{}

	Texture::Texture(SDL_Texture* texture)
		: m_texutre(texture), m_pos(VEC2_ZERO), m_rotation(0), m_width(0), m_height(0), m_active(false)
	{
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);
	}

	void Texture::Set(SDL_Texture* texture)
	{
		m_texutre = texture;
		m_active = true;
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);
	}

	void Texture::Set(SDL_Texture* texture, Vector2D pos, float rotation)
	{
		Set(texture);
		m_pos = pos;
	}

	void Texture::Set(SDL_Texture* texture, float x, float y, float rotation)
	{
		Set(texture);
		m_pos = Vector2D(x, y);
	}
}
