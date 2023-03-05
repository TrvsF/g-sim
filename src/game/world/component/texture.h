#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h> // TODO: only texture

#include "../src/util/vector2d.h"

namespace object
{
	enum class TextureType
	{
		Static,
		Dynamic
	};

	struct DynamicData
	{
		int frames = 0;
		int offset = 0;
	};

	class Texture
	{
	protected:
		SDL_Texture*	m_texutre;
		TextureType		m_type;
		DynamicData		m_data;
		int				m_frame = 0;
		Vector2D		m_pos;
		float			m_rotation;
		float			m_scale;
		int				m_width;
		int				m_height;
		bool			m_active;

	public:
		Texture();
		Texture(SDL_Texture* texture);

		void Set(SDL_Texture* texture);
		void Set(SDL_Texture* texture, Vector2D pos, float rotation);
		void Set(SDL_Texture* texture, Vector2D pos, float rotation, int frames, int offset);

		inline SDL_Texture* GetTexture();

		inline bool IsInitialized();

		inline TextureType Type() 
		{ return m_type; }
		inline DynamicData& Data()
		{ return m_data; }

		inline int Frame() { return m_frame; }
		inline void Frame(int frame) { m_frame = frame; }

		inline void Rotation(float rotation);
		inline float Rotation() const;

		inline void Width(int width);
		inline int Width() const;

		inline void Height(int height);
		inline int Height() const;

		inline void Pos(Vector2D pos);
		inline Vector2D Pos() const;

		inline void Active(bool active);
		inline bool Active();

		inline void Scale(float scale);
		inline float Scale();

		inline void OffsetPos(Vector2D offset);
		inline void OffsetRotation(float rotation);
	};
}
#include "texture-inl.h"

#endif // !TEXTURE_H_