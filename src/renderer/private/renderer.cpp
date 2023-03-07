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

		m_globalscale = 1.0f;
		m_count = 0;
	}

	Renderer::~Renderer()
	{
	}

	SDL_Texture* Renderer::GetSetTextureObjFromId(const char* id, object::Texture* texture_obj)
	{
		add_texture_object(texture_obj);
		return m_assets->GetTexture(id);
	}

	SDL_Texture* Renderer::GetSetTextureObjFromText(const char* font, std::string text, SDL_Color colour, object::Texture* texture_obj)
	{
		if (texture_obj != nullptr) { add_texture_object(texture_obj); }
		return create_texture_from_text(font, text, colour);
	}

	SDL_Texture* Renderer::create_texture_from_text(const char* font, std::string text, SDL_Color colour)
	{
		TTF_Font* fontobj = m_assets->GetFont(font);
		SDL_Surface* tempsurface = TTF_RenderText_Solid(fontobj, text.c_str(), colour);
		if (!tempsurface) { return nullptr; } // TODO : ERROR

		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, tempsurface);
		SDL_FreeSurface(tempsurface);

		return texture;
	}

	void Renderer::LoadAllTextures()
	{
		// get local path
		std::string path = m_assets->GetFullTexturePath();

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			std::string entry_str = entry.path().string();
			std::string entry_stem_str = entry.path().stem().string();

			// check if texture image already exists in memory
			SDL_Texture* texture = m_assets->GetTexture(entry_str);
			if (!texture)
			{
				// load the texture
				SDL_Surface* tempsurface = IMG_Load(entry_str.c_str());
				if (!tempsurface) { continue; } // TODO : ERROR
				texture = SDL_CreateTextureFromSurface(m_renderer, tempsurface);
				SDL_FreeSurface(tempsurface);

				// add the texture to asset manager
				m_assets->SetTexture(entry_stem_str, texture);
			}
		}
	}

	void Renderer::LoadAllFonts()
	{
		// get local path
		std::string path = m_assets->GetFullFontPath();

		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			std::string entry_str = entry.path().string();
			std::string entry_stem_str = entry.path().stem().string();

			// check if font already exists in memory
			TTF_Font* font = m_assets->GetFont(entry_stem_str);
			if (!font)
			{
				// load the texture
				font = TTF_OpenFont(entry_str.c_str(), 18);
				m_assets->SetFont(entry_stem_str, font);
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

		// init images
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) { return false; }

		// init fonts
		if (TTF_Init() == -1) { return false; }

		// create the asset manager object
		m_assets = new Assets();

		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		LoadAllFonts();
		LoadAllTextures();
		set_window_icon();

		return true;
	}

	void Renderer::Render()
	{
		clear_buffer();	

		for (object::Geometry* geometryobj : m_geometryobjects)
		{
			if (!geometryobj->Active()) { continue; }

			render_geometry_object(geometryobj);
		}

		if (console::ACTIVE)
		{
			render_console();
		}

		for (object::Texture* textureobj : m_textureobjects)
		{
			if (!textureobj->Active()) { continue; }

			render_texture_object(textureobj);
		}

		for (object::AABB* aabb : m_aabbs)
		{
			render_aabb(aabb);
		}

		m_count++; // TODO : better way to do this?
		// !!! the last thing to be called from renderer
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::Clean()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_Quit();
	}

	void Renderer::UnloadTexture(object::Texture* texture_object)
	{
		auto it = std::find(m_textureobjects.begin(), m_textureobjects.end(), texture_object);
		if (it != m_textureobjects.end()) { m_textureobjects.erase(it); }
	}

	void Renderer::LoadGeometry(object::Geometry* geometry_object)
	{
		m_geometryobjects.push_back(geometry_object);
	}

	void Renderer::UnloadGeometry(object::Geometry* geometry_object)
	{
		auto it = std::find(m_geometryobjects.begin(), m_geometryobjects.end(), geometry_object);
		if (it != m_geometryobjects.end()) { m_geometryobjects.erase(it); }
	}

	void Renderer::LoadAABB(object::AABB* aabb)
	{
		m_aabbs.push_back(aabb);
	}

	void Renderer::UnloadAABB(object::AABB* aabb)
	{
		auto it = std::find(m_aabbs.begin(), m_aabbs.end(), aabb);
		if (it != m_aabbs.end()) { m_aabbs.erase(it); }
	}

	void Renderer::set_window_icon()
	{
		SDL_Surface* icon_surface = IMG_Load(m_assets->GetPathToTexture("icon.png").c_str());
		SDL_SetWindowIcon(m_window, icon_surface);
	}

	void Renderer::render_texture_object(object::Texture* texture_object)
	{
		// float scale		= m_globalscale;
		float scale		= 1;
		/*
		int width		= (int)roundf(texture_object->Width()  * scale);
		int height		= (int)roundf(texture_object->Height() * scale);
		*/
		int width  = texture_object->Width();
		int height = texture_object->Height();
		int x			= (int)roundf(texture_object->Pos().x - (((width * scale) - width) / 2));
		int y			= (int)roundf(texture_object->Pos().y - (((height * scale) - height) / 2));
		float rotation  = texture_object->Rotation();

		int offsetx = 0;
		int offsety = 0;
		if (texture_object->Type() == object::TextureType::Dynamic)
		{
			int xframes = texture_object->Data().xframes;
			int yframes = 2;
			width  /= xframes;
			height /= yframes;
			
			int currentxframe = texture_object->CurrentXFrame();
			int currentyframe = texture_object->CurrentYFrame();
			
			// TODO : clean
			if (currentxframe >= 0)
			{
				offsetx = width * currentxframe;
			}
			else
			{
				int fx = roundf(m_count / -currentxframe);
				offsetx = width * (fx % xframes);
			}

			if (currentyframe >= 0)
			{
				offsety = width * currentyframe;
			}
			else
			{
				int fy = roundf(m_count / -currentyframe);
				offsety = width * (fy % yframes);
			}
		}

		SDL_Rect render_rect // big
		{ x, y, width * scale, height * scale };
		SDL_Rect src_rect	 // little
		{ offsetx, offsety, width, height };

		SDL_RenderCopyEx(m_renderer, texture_object->GetTexture(), &src_rect, &render_rect, rotation, NULL, SDL_FLIP_NONE);
	}
	
	void Renderer::render_geometry_object(object::Geometry* geometry)
	{

		float ang = geometry->Rotation();
		float scale = m_globalscale;
		Vector2D midpoint = VEC2_ZERO;
		for (const auto& tri : geometry->Tris())
		{
			// hack : find midpoint
			for (Vector2D vec1 : geometry->Tris()[0].GetPoints())
			{
				for (Vector2D vec2 : geometry->Tris()[1].GetPoints())
				{
					if (vec1 == vec2) 
					{
						midpoint = vec1; break; 
					}
				}
			}
			midpoint = midpoint * m_globalscale;

			// create base verts
			Vector2D offsetpos = geometry->Pos();
			Vector2D v1 = (tri.GetPoint1() * scale) + offsetpos;
			Vector2D v2 = (tri.GetPoint2() * scale) + offsetpos;
			Vector2D v3 = (tri.GetPoint3() * scale) + offsetpos;
			// rotate
			maths::GetRotatedPoint(v1, midpoint + offsetpos, ang);
			maths::GetRotatedPoint(v2, midpoint + offsetpos, ang);
			maths::GetRotatedPoint(v3, midpoint + offsetpos, ang);
			
			SDL_FPoint p1 = { v1.x, v1.y };
			SDL_FPoint p2 = { v2.x, v2.y };
			SDL_FPoint p3 = { v3.x, v3.y };

			std::vector< SDL_Vertex > v = {
				{ p1, geometry->Colour()},
				{ p2, geometry->Colour()},
				{ p3, SDL_Color{ 0, 0, 0, 200 } }
			};
			SDL_RenderGeometry(m_renderer, nullptr, v.data(), (int)v.size(), nullptr, 0);
		}
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
		rect.w = (int)roundf(m_width / 2.5f);
		rect.h = 20;
		rect.x = 3;
		rect.y = 3;

		render_fillrect(rect, { 255, 30, 30, 150 }, { 0, 0, 0, 255 });
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