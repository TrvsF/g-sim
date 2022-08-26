#ifndef TEXTUREOBJECT_H_
#define TEXTUREOBJECT_H_ 

#include "game-object.h"

namespace object
{
	class TextureObject : public GameObject
	{
	private:
		Texture* m_texture;

		void set_texture_from_id(const char* id);
	public:
		TextureObject(Object* object, const char* textureid);

		inline Texture* GetTexture();
	};
}

#include "texture-object-inl.h"

#endif // _TEXTUREOBJECT_H_