#ifndef CAMERA2_H_
#define CAMERA2_H_

#include "../game/world/component/texture.h"
#include "../game/world/component/geometry.h"

#include <vector>
#include <string>

namespace renderer
{
	class Camera
	{
	private:
		Vector2D m_pos;
		float m_zoom;

		object::Texture* m_subject; // TODO : for geom too
		std::vector<object::Texture*>*  m_textures;
		std::vector<object::Geometry*>* m_geometry;
		std::string m_name;

		inline void offset_pos(Vector2D offset)
		{ m_pos += offset; }
	
		inline void offset_zoom(float offset) 
		{ m_zoom += offset; }
	public:
		Camera(std::vector<object::Texture*>* textures,
			std::vector<object::Geometry*>* geometry);

		void Update();

		inline std::string* GetName() { return &m_name; }
	};
}
#endif