#ifndef TEXTOBJECT_H_
#define TEXTOBJECT_H_ 

#include "../src/game/object/game-object.h"
#include "../src/game/object/component/texture.h"
#include "../src/renderer/renderer.h"

namespace object
{
	class TextObject : public GameObject
	{
	private:
		Texture* m_texture;

		const char* m_font;
		std::string m_text;
		SDL_Color m_colour;

		void set_text(const char* font, std::string text, SDL_Color colour);
		void update_text();
	public:
		TextObject(GameObject* object, const char* font, std::string text, SDL_Color colour);

		void SetText(std::string text);
		void SetColour(SDL_Color colour);
		void HandleOffsets();
		void Update();

		inline Texture* GetTexture()
		{
			return m_texture;
		}
	};
}

#endif