#include "../renderer.h"

namespace renderer
{
	Renderer* Renderer::s_instance = nullptr;

	Renderer::Renderer()
	{
		m_window = nullptr;
		m_renderer = nullptr;

		m_title = "";
		m_width = 0;
		m_height = 0;
	}

	Renderer::~Renderer()
	{
		Destroy();
	}

	void Renderer::Create()
	{
		if (!Renderer::s_instance)
		{
			Renderer::s_instance = new Renderer();
		}
	}

	Renderer* Renderer::Get()
	{
		return Renderer::s_instance;
	}

	void Renderer::Destroy()
	{
		SAFE_DELETE(s_instance);
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

		return true;

	}

	void Renderer::ClearBuffer()
	{
		SDL_RenderClear(m_renderer);
	}

	void Renderer::Render()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::Clean()
	{
		SDL_DestroyWindow(m_window);
		SDL_DestroyRenderer(m_renderer);
		SDL_Quit();
	}

}


