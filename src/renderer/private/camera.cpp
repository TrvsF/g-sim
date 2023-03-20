#include "../camera.h"

namespace renderer
{
	Camera::Camera(std::vector<object::Texture*>* textures,
		std::vector<object::Geometry*>* geometry)
	{
		m_textures = textures;
		m_geometry = geometry;
		
		m_name = std::to_string(maths::GetRandomInt(5000, 50)); // TODO : not this
	}

	void Camera::Update()
	{
		m_pos = m_subject->CenterPos();
	}
}