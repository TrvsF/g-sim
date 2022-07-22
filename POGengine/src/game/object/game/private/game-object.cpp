#include "../game-object.h"

namespace object
{
	GameObject::GameObject(Object* object, Texture* texture)
		: m_object(object), m_texture(texture)
	{}

}