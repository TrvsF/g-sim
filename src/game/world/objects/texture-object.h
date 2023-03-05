#ifndef TEXTUREOBJECT_H_
#define TEXTUREOBJECT_H_ 

#include "../src/game/world/game-object.h"
#include "../src/game/world/component/texture.h"
#include "../src/renderer/renderer.h"

namespace object
{
	inline std::shared_ptr<_EventBus> bus = event::Event::SharedInstace().EventBus;
	class TextureObject : public GameObject
	{
	private:
		Texture*	m_texture;

		void set_texture_from_id(const char* id, int frames, int offset);
	public:
		TextureObject(GameObject* object, const char* textureid);
		TextureObject(GameObject* object, const char* textureid, int frames, int offset);
		~TextureObject();

		void HandleOffsets();
		void Update();

		inline Texture* GetTexture();
	};
}

#include "texture-object-inl.h"

#endif // _TEXTUREOBJECT_H_