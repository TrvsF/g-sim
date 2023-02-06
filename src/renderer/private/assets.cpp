#include "../assets.h"

namespace renderer
{
	Assets::Assets()
	{
		m_asset_path = get_asset_path();
	}

	Assets::~Assets()
	{
		for (const auto &texture : m_textures)
		{
			if (texture.second != NULL)
			{
				SDL_DestroyTexture(texture.second);
			}
		}
		m_textures.clear();
	}

	void Assets::SetTexture(std::string full_path, SDL_Texture* texture)
	{
		m_textures[full_path] = texture;
	}

	SDL_Texture* Assets::GetTexture(std::string full_path)
	{
		return m_textures[full_path];
	}

	void Assets::SetFont(std::string full_path, TTF_Font* font)
	{
		m_fonts[full_path] = font;
	}

	TTF_Font* Assets::GetFont(std::string full_path)
	{
		return m_fonts[full_path];
	}

	std::string Assets::GetPathToTexture(const char* path_to_texture)
	{
		std::string path = m_asset_path + "textures/" + std::string(path_to_texture);
		return path;
	}

	std::string Assets::GetFullTexturePath()
	{
		return m_asset_path + "textures/";
		
	}

	std::string Assets::GetFullFontPath()
	{
		return m_asset_path + "fonts/";
	}

	std::string Assets::get_asset_path()
	{
		// get full path
		std::string full_path = SDL_GetBasePath();
		std::stringstream full_path_ss(full_path);
		
		// split into segments (we're looking for "/out")s
		std::vector<std::string> path_list;
		std::string segment;
		while(std::getline(full_path_ss, segment, '\\'))
		{
			path_list.push_back(segment);
		}

		// make new vector string:))) and then add everything before the out dir [THANKS SDL]
		std::vector<std::string> real_path_list;
		for (std::string path : path_list)
		{
			if (path == "out")
				break;

			real_path_list.push_back(path);
		}

		// set the asset path with "/"s
		std::string asset_path;
		for (std::string path : real_path_list)
		{
			asset_path.append(path);
			asset_path.append("/");
		}

		asset_path.append("assets/");

		return asset_path;
	}

}