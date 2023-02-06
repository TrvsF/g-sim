#ifndef TEXTUREOBJECT_H_
#define TEXTUREOBJECT_H_ 

#include "../src/game/object/game-object.h"
#include "../src/game/object/component/texture.h"
#include "../src/renderer/renderer.h"

namespace object
{
	class TextureObject : public GameObject
	{
	private:
		Texture*	m_texture;

		void set_texture_from_id(const char* id);
		void set_text(const char* font, std::string text, SDL_Color colour);
	public:
		TextureObject(GameObject* object, const char* textureid);
		TextureObject(GameObject* object, const char* font, std::string text, SDL_Color colour);

		void HandleOffsets();
		void Update();

		inline Texture* GetTexture();
	};
}

#include "texture-object-inl.h"

#endif // _TEXTUREOBJECT_H_