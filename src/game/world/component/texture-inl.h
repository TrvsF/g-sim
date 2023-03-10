#include "texture.h"

namespace object
{
	inline bool Texture::IsInitialized()
	{
		return !(m_texture == nullptr);
	}

	inline SDL_Texture* Texture::GetTexture()
	{
		return m_texture;
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

	inline void Texture::OffsetPos(Vector2D offset)
	{
		m_pos += offset;
	}

	inline void Texture::OffsetRotation(float rotation)
	{
		m_rotation += rotation;
	}

	inline void Texture::Active(bool active)
	{
		m_active = active;
	}

	inline bool Texture::Active()
	{
		return m_active;
	}

	inline void Texture::Scale(float scale)
	{
		m_scale = scale;
	}

	inline float Texture::Scale()
	{
		return m_scale;
	}
}