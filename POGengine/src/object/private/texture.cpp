#include "../texture.h"

namespace object
{
	Texture::Texture()
	{
		m_width = 0;
		m_height = 0;
		m_rotation = 0;
		m_pos = VEC2_ZERO;
	}

	Texture::~Texture()
	{
	}

	void Texture::Set(SDL_Texture* texture)
	{
		m_texutre = texture;
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);
	}

	void Texture::Set(SDL_Texture* texture, float x, float y, float rotation)
	{
		m_texutre = texture;
		SDL_QueryTexture(m_texutre, NULL, NULL, &m_width, &m_height);

		m_pos = Vector2D(x, y);
		m_rotation = rotation;
	}

	SDL_Texture* Texture::GetTexture()
	{
		return m_texutre;
	}

	void Texture::Width(int width)
	{
		m_width = width;
	}

	int Texture::Width()
	{
		return m_width;
	}

	void Texture::Height(int height)
	{
		m_height = height;
	}

	int Texture::Height()
	{
		return m_height;
	}

	void Texture::Rotation(float rotation)
	{
		m_rotation = rotation;
	}

	float Texture::Rotation()
	{
		return m_rotation;
	}

	void Texture::Pos(Vector2D pos)
	{
		m_pos = pos;
	}

	Vector2D Texture::Pos()
	{
		return m_pos;
	}
}
