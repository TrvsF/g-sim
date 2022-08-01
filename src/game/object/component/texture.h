#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>

#include "../src/util/vector2d.h"

namespace object
{
	class Texture
	{
	protected:
		SDL_Texture*	m_texutre;
		Vector2D		m_pos;
		float			m_rotation;
		int				m_width;
		int				m_height;

	public:
		Texture();
		Texture(SDL_Texture* texture);

		void Set(SDL_Texture* texture);
		void Set(SDL_Texture* texture, Vector2D pos, float rotation);
		void Set(SDL_Texture* texture, float x, float y, float rotation);

		inline SDL_Texture* GetTexture();

		inline bool IsInitialized();

		inline void Rotation(float rotation);
		inline float Rotation() const;

		inline void Width(int width);
		inline int Width() const;

		inline void Height(int height);
		inline int Height() const;

		inline void Pos(Vector2D pos);
		inline Vector2D Pos() const;

		inline void OffsetPos(Vector2D offset);
	};
}

#include "texture-inl.h"

#endif // !TEXTURE_H_