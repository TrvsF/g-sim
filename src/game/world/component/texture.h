#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>

#include "../src/util/vector2d.h"

namespace object
{
	enum class TextureType
	{
		Text,
		Static,
		Dynamic
	};

	struct DynamicData
	{
		int xframes = 0;
		int yframes = 0;
	};

	class Texture
	{
	protected:
		SDL_Texture*	m_texture;
		TextureType		m_type;
		DynamicData		m_data;
		Vector2D		m_pos;
		Vector2D		m_scaleoffset;
		int				m_xcurrentframe;
		int				m_ycurrentframe;
		float			m_rotation;
		float			m_scale;
		int				m_width;
		int				m_height;
		int				m_twidth;
		int				m_theight;
		bool			m_active;

	public:
		Texture();
		Texture(SDL_Texture* texture);

		void Set(SDL_Texture* texture);
		void SetStatic(SDL_Texture* texture, Vector2D pos, float rotation, int width, int height);
		void SetAnimated(SDL_Texture* texture, Vector2D pos, float rotation, int frames, int width, int height);
		void SetText(SDL_Texture* texture, Vector2D pos, float rotation, int width, int height);


		inline SDL_Texture* GetTexture();

		inline bool IsInitialized();

		inline TextureType Type() 
		{ return m_type; }
		inline DynamicData& Data()
		{ return m_data; }

		inline void CurrentXFrame(int xframe)
		{ m_xcurrentframe = xframe; }
		inline int CurrentXFrame()
		{ return m_xcurrentframe; }
		inline void CurrentYFrame(int yframe)
		{ m_ycurrentframe = yframe; }
		inline int CurrentYFrame()
		{ return m_ycurrentframe; }

		inline Vector2D Offsetscale()
		{ return m_scaleoffset; }
		inline void Offsetscale(Vector2D pos)
		{ m_scaleoffset = pos; }

		inline void Pos(Vector2D pos)
		{ m_pos = pos; }
		inline Vector2D Pos() const
		{ return m_pos; }
		inline Vector2D CenterPos() const
		{ return Vector2D{ m_pos.x + (m_width / 2), m_pos.y + (m_height / 2) }; }

		inline void Rotation(float rotation);
		inline float Rotation() const;

		inline void Width(int width);
		inline int Width() const;

		inline void Height(int height);
		inline int Height() const;

		inline int THeight() { return m_theight; }
		inline int TWidth()  { return m_twidth; }

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