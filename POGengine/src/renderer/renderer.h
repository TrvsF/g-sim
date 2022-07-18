#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL.h>
#include <SDL_image.h>

#include "../src/engine/helper_macos.h"

namespace renderer
{
	class Renderer
	{
	private:
		static Renderer* s_instance;

		int m_width;
		int m_height;
		const char* m_title;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		inline void resize_window();

	public:
		Renderer();
		virtual ~Renderer();

		static void Create();
		static Renderer* Get();
		static void Destroy();

		SDL_Texture* LoadTexture(const char* path_to_texture);

		bool Start(const char* window_title, int width, int height);

		void ClearBuffer();
		void Render();
		void Clean();

	};
}

#endif