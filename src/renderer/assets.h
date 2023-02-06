#ifndef ASSETS_H_
#define ASSETS_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include <map>
#include <string>
#include <sstream>

namespace renderer
{
	class Assets
	{
	private:
		std::string m_asset_path;
		std::map<std::string, SDL_Texture*> m_textures;
		std::map<std::string, TTF_Font*>	m_fonts;

		std::string get_asset_path();
	public:
		Assets();
		virtual ~Assets();

		void SetTexture	(std::string full_path, SDL_Texture* texture);
		SDL_Texture*	GetTexture(std::string full_path);
		void SetFont	(std::string full_path, TTF_Font* font);
		TTF_Font*		GetFont(std::string full_path);

		std::string GetPathToTexture(const char* path_to_texture);
		std::string GetFullTexturePath();
		std::string GetFullFontPath();
	};
}

#endif