#ifndef ASSETS_H_
#define ASSETS_H_

#include <SDL.h>

#include <map>

namespace renderer
{
	class Assets
	{
	private:
		std::map<const char*, SDL_Texture*> m_textures;
		
	public:
		Assets();
		virtual ~Assets();

		void SetTexture(const char* path_to_texture, SDL_Texture* texture);
		SDL_Texture* GetTexture(const char* path_to_texture);
	};
}

#endif