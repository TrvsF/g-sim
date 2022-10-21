#include "texture.h"

namespace object
{
	inline bool Texture::IsInitialized()
	{
		return !(m_texutre == nullptr);
	}

	inline SDL_Texture* Texture::GetTexture()
	{
		return m_texutre;
	}

	inline void Texture::Rotation(float rotation)
	{
		m_rotation = rotation;
	}

	inline float Texture::Rotation() const
	{
		return m_rotation;
	}

	inline void Texture::Width(int width)
	{
		m_width = width;
	}

	inline int Texture::Width() const
	{
		return m_width;
	}

	inline void Texture::Height(int height)
	{
		m_height = height;
	}

	inline int Texture::Height() const
	{
		return m_height;
	}

	inline void Texture::Pos(Vector2D pos)
	{
		m_pos = pos;
	}

	inline Vector2D Texture::Pos() const
	{
		return m_pos;
	}

	inline void Texture::OffsetPos(Vector2D offset)
	{
		m_pos = m_pos + offset;
	}

	inline void Texture::Active(bool active)
	{
		m_active = active;
	}

	inline bool Texture::Active()
	{
		return m_active;
	}
}