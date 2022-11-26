#include "../geometry-object.h"

namespace object
{
	GeometryObject::GeometryObject(GameObject* object)
		: GameObject(object)
	{
		m_tris.push_back(Triangle::Create({ 50, 50 }, { 60, 100 }, {70, 70}));

		m_rotate = 0;
		m_debug = true;

		renderer::Renderer::Get()->LoadTri(&m_tris.front());
	}
}