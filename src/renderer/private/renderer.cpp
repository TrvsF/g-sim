#include "../renderer.h"

namespace renderer
{
	Renderer* Renderer::s_instance = nullptr;

	Renderer::Renderer()
	{
		m_num_texture_objects = 0;

		m_window	= nullptr;
		m_renderer	= nullptr;
		m_assets	= nullptr;

		m_title		= "";
		m_width		= 0;
		m_height	= 0;
	}

	Renderer::~Renderer()
	{
		Destroy();
	}

	void Renderer::Create()
	{
		if (!s_instance)
		{
			s_instance = new Renderer();
		}
	}

	void Renderer::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	SDL_Texture* Renderer::GetSetTextureFromId(const char* id, object::Texture* texture_obj)
	{
		add_texture_object(texture_obj);
		return m_assets->GetTexture(id);
	}

	void Renderer::LoadAllTextures()
	{
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

		LoadAllTextures();

		return true;
	}

	void Renderer::Render()
	{
		clear_buffer();

		for (size_t i = 0; i < m_num_texture_objects; i++)
		{
			render_texture_object(m_texutre_objects[i]);
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

	inline void Renderer::add_texture_object(object::Texture* texture_object)
	{
		m_texutre_objects.push_back(texture_object);
		m_num_texture_objects++;
	}

	void Renderer::render_texture_object(object::Texture* texture_object)
	{
		SDL_Rect render_rect{};
		int x			= (int)(texture_object->Pos().x);
		int y			= (int)(texture_object->Pos().y);
		int width		= texture_object->Width();
		int height		= texture_object->Height();
		float rotation  = texture_object->Rotation();

		render_rect.x = x - width;
		render_rect.y = y - height;
		render_rect.w = width;
		render_rect.h = height;

		SDL_RenderCopyEx(m_renderer, texture_object->GetTexture(), NULL, &render_rect, rotation, NULL, SDL_FLIP_NONE);
	}

	void Renderer::clear_buffer()
	{
		SDL_RenderClear(m_renderer);
	}

}