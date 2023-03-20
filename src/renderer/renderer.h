#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "../base/helper_macos.h"
#include "../game/world/component/aabb.h"
#include "../game/world/component/texture.h"
#include "../game/world/component/geometry.h"
#include "../base/console.h"
#include "../event/event.h"
#include "camera.h"
#include "assets.h"

#include <dexode/EventBus.hpp>
using Listener = dexode::EventBus::Listener;

namespace renderer
{
	class Renderer // TODO : move console & window
	{
	private:
		// window things : TODO move
		int				m_width;
		int				m_height;
		const char*		m_title;

		Vector2D		m_scalepos;
		float			m_globalscale;
		long			m_count;

		SDL_Window*		m_window;
		SDL_Renderer*	m_renderer;

		Camera*			m_camera;
		Assets*			m_assets;

		bool			m_debugrender;

		Listener m_listener{ event::Event::SharedInstace().EventBus };
		void e_renderaabbchange(const event::eSetDrawAABB& event);

		std::vector<object::AABB*>		m_aabbs;
		std::vector<object::Geometry*>	m_geometryobjects;
		std::vector<object::Texture*>	m_textureobjects;

		void render_geometry_object(object::Geometry* geometry_object);
		void render_texture_object (object::Texture* texture_object);
		void render_aabb		   (object::AABB* aabb);
		void render_rect		   (SDL_Rect rect, SDL_Color colour);
		void render_fillrect	   (SDL_Rect rect, SDL_Color outline, SDL_Color fill);

		inline void add_texture_object(object::Texture* texture_object)
		{ m_textureobjects.push_back(texture_object); }

		SDL_Texture* create_texture_from_text(const char* font, std::string text, SDL_Color colour);

		void render_console();
		void set_window_icon();
		void clear_buffer();

		Renderer();
		virtual ~Renderer();
	public:
		static Renderer& SharedInstace() { static Renderer renderer; return renderer; }
		
		SDL_Texture* ReplaceText(const char* font, std::string text, SDL_Color colour, object::Texture* texture_obj);
		SDL_Texture* GetSetTextureObjFromText(const char* font, std::string text, SDL_Color colour, object::Texture* texture_obj);
		SDL_Texture* GetSetTextureObjFromId(const char* id, object::Texture* texture_obj);
		void LoadAllTextures();

		void LoadAllFonts();

		void UnloadAABB(object::AABB* aabb);
		void LoadAABB  (object::AABB* aabb);
		void UnloadGeometry(object::Geometry* geometry_object);
		void LoadGeometry  (object::Geometry* geometry_object);
		void UnloadTexture (object::Texture* texture_object);

		inline Vector2D GetScreensize()
		{ return { (float)m_width, (float)m_height }; }

		inline void Scale(float scale)
		{ m_globalscale = scale; }
		inline float Scale()
		{ return m_globalscale; }

		inline void ScalePos(Vector2D scalepos)
		{ m_scalepos = scalepos; }

		bool Start(const char* window_title, int width, int height);
		void Render();
		void Clean();
	};
}
#endif