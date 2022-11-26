#ifndef _RENDERER_H
#define _RENDERER_H

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "../base/helper_macos.h"
#include "../game/object/component/texture.h"
#include "../renderer/assets.h"

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
		Assets* m_assets;

		std::vector<SDL_Rect> m_shape_objects;
		std::vector<SDL_Vertex> m_verts;
		std::vector<object::Texture*> m_texutre_objects;

		void render_verts(std::vector<SDL_Vertex> verts);

		void render_shape_object(SDL_Rect shape);
		void reset_shape_objects();

		void add_texture_object(object::Texture* texture_object);
		void render_texture_object(object::Texture* texture_object);

		void set_window_icon();

		void clear_buffer();

		Renderer();
		virtual ~Renderer();
	public:
		static void Create();
		static inline Renderer* Get();
		static void Destroy();

		void LoadAllTextures();
		SDL_Texture* GetSetTextureObjFromId(const char* id, object::Texture* texture_obj);

		void AddTempShape(SDL_Rect shape);
		void AddVerts(std::vector<SDL_Vertex> verts);

		inline SDL_Renderer* GetRendererObj();

		inline Vector2D GetScreensize();

		bool Start(const char* window_title, int width, int height);
		void Render();
		void Clean();
	};
}

#include "renderer-inl.h"

#endif