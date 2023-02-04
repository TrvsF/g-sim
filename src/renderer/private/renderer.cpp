#include "../renderer.h"

namespace renderer
{
	Renderer::Renderer()
	{
		m_window	= nullptr;
		m_renderer	= nullptr;
		m_assets	= nullptr;

		m_title		= "";
		m_width		= 0;
		m_height	= 0;
	}

	Renderer::~Renderer()
	{
	}

	SDL_Texture* Renderer::GetSetTextureObjFromId(const char* id, object::Texture* texture_obj)
	{
		add_texture_object(texture_obj);
		return m_assets->GetTexture(id);
	}

	void Renderer::LoadAllTextures()
	{
		// get local path
		std::string path = m_assets->GetPath();

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			std::string entry_str = entry.path().string();
			std::string entry_stem_str = entry.path().stem().string();

			// check if texture image already exists in memory
			SDL_Texture* texture = m_assets->GetTexture(entry_str);
			if (!texture)
			{
				// load the texture
				SDL_Surface* temp_surface = IMG_Load(entry_str.c_str());
				if (!temp_surface) { continue; } // TODO : ERROR
				texture = SDL_CreateTextureFromSurface(m_renderer, temp_surface);
				SDL_FreeSurface(temp_surface);

				// add the texture to asset manager
				m_assets->SetTexture(entry_stem_str, texture);
			}
		}
	}

	bool Renderer::Start(const char* window_title, int width, int height)
	{
		m_title = window_title;
		m_width = width;
		m_height = height;

		// start the SDL libs we need
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { return false; }

		// create the window SDL object
		m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
		if (!m_window) { return false; }

		// create the renderer SDL object
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (!m_renderer) { return false; }

		// create the asset manager object
		m_assets = new Assets();

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		LoadAllTextures();
		set_window_icon();

		return true;
	}

	void Renderer::Render()
	{
		clear_buffer();

		for (object::Texture* textureobj : m_texutre_objects)
		{
			if (!textureobj->Active()) { continue; }

			render_texture_object(textureobj);
		}		

		for (object::Geometry* geometryobj : m_geometry_objects)
		{
			if (!geometryobj->Active()) { continue; }

			render_geometry_object(geometryobj);
		}

		for (object::AABB* aabb : m_aabbs)
		{
			render_aabb(aabb);
		} 

		if (console::ACTIVE)
		{
			render_console();
		}

		// !!! the last thing to be called from renderer
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::Clean()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_Quit();
	}

	void Renderer::LoadGeometry(object::Geometry* geometry_object)
	{
		m_geometry_objects.push_back(geometry_object);
	}

	void Renderer::LoadAABB(object::AABB* aabb)
	{
		m_aabbs.push_back(aabb);
	}

	void Renderer::set_window_icon()
	{
		SDL_Surface* icon_surface = IMG_Load(m_assets->GetFullPath("icon.png").c_str());
		SDL_SetWindowIcon(m_window, icon_surface);
	}

	void Renderer::render_texture_object(object::Texture* texture_object)
	{
		float scale		= texture_object->Scale();
		int width		= texture_object->Width();
		int height		= texture_object->Height();
		int x			= texture_object->Pos().x - (((width * scale) - width) / 2);
		int y			= texture_object->Pos().y - (((height * scale) - height) / 2);
		float rotation  = texture_object->Rotation();

		SDL_Rect render_rect {
			x, y, (int)roundf(width * scale), (int)roundf(height * scale)
		};

		SDL_Rect src_rect {
			0, 0, (int)roundf(width * scale), (int)roundf(height * scale)
		};

		SDL_RenderCopyEx(m_renderer, texture_object->GetTexture(), NULL, &render_rect, rotation, NULL, SDL_FLIP_NONE);
	}
	
	void Renderer::render_geometry_object(object::Geometry* geometry_object)
	{
		for (const auto& tri : geometry_object->Tris())
		{
			std::vector< SDL_Vertex > v = {
				{ SDL_FPoint{ tri.GetPoint1().x + geometry_object->Pos().x, tri.GetPoint1().y + geometry_object->Pos().y }, SDL_Color{ 50, 130, 0, 255}},
				{ SDL_FPoint{ tri.GetPoint2().x + geometry_object->Pos().x, tri.GetPoint2().y + geometry_object->Pos().y }, SDL_Color{ 50, 130, 0, 255 } },
				{ SDL_FPoint{ tri.GetPoint3().x + geometry_object->Pos().x, tri.GetPoint3().y + geometry_object->Pos().y }, SDL_Color{ 0, 0, 0, 255 } }
			};
			SDL_RenderGeometry(m_renderer, nullptr, v.data(), (int)v.size(), nullptr, 0);
		}
	}

	void Renderer::render_tri(object::Triangle* tri)
	{
		/*
		std::vector< SDL_Vertex > v = {
				{ SDL_FPoint{ tri->GetPoint1() }, SDL_Color{255, 0, 0, 255}},
				{ SDL_FPoint{ tri->GetPoint2() }, SDL_Color{ 0, 0, 255, 255 } },
				{ SDL_FPoint{ tri->GetPoint3() }, SDL_Color{ 0, 255, 0, 255 } }
		};
		SDL_RenderGeometry(m_renderer, nullptr, v.data(), v.size(), nullptr, 0);
		*/
	}

	void Renderer::render_aabb(object::AABB* aabb)
	{
		SDL_Rect rect;
		rect.w = (int)aabb->GetMaxX() - (int)aabb->GetMinX();
		rect.h = (int)aabb->GetMaxY() - (int)aabb->GetMinY();
		rect.x = (int)aabb->GetMinX();
		rect.y = (int)aabb->GetMinY();

		render_rect(rect, { 255, 30, 30, 255 });
	}

	void Renderer::render_console()
	{
		SDL_Rect rect;
		rect.w = m_width / 2.5f;
		rect.h = m_height / 4.0f;
		rect.x = 3;
		rect.y = 3;

		render_fillrect(rect, { 255, 30, 30, 150 }, { 150, 150, 150, 255 });
	}

	void Renderer::render_rect(SDL_Rect rect, SDL_Color colour)
	{
		SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
		SDL_RenderDrawRect(m_renderer, &rect);

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	}

	void Renderer::render_fillrect(SDL_Rect rect, SDL_Color outline, SDL_Color fill)
	{
		SDL_SetRenderDrawColor(m_renderer, fill.r, fill.g, fill.b, fill.a);
		SDL_RenderFillRect(m_renderer, &rect);

		SDL_SetRenderDrawColor(m_renderer, outline.r, outline.g, outline.b, outline.a);
		SDL_RenderDrawRect(m_renderer, &rect);

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	}

	void Renderer::clear_buffer()
	{
		SDL_RenderClear(m_renderer);
	}

}