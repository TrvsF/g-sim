#ifndef ASSETS_H_
#define ASSETS_H_

#include <SDL.h>

#include <string>
#include <map>

#include "../renderer/renderer.h"

namespace renderer
{
	class Assets
	{
	private:
		static Assets* s_instance;

		std::map<std::string, SDL_Texture*> m_textures;
		
	public:
		Assets();
		virtual ~Assets();

		static void Create();
		static Assets* Get();
		static void Destroy();

		SDL_Texture* GetTexture(const char* path_to_texture);
	};
}

#endif