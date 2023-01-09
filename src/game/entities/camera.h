#ifndef CAMERA_H_
#define CAMERA_H_

#include "../object/game-object.h"
#include "../object/objects/texture-object.h"
#include "../object/objects/geometry-object.h"
#include "../object/component/geometry.h"
#include "../object/component/texture.h"

namespace object
{
	class Camera : public GameObject
	{
	private:
		GameObject*				m_subject;
		std::vector<Texture*>	m_textureobjs;
		Vector2D				m_screensize;
		Vector3D				m_local_offset_pos;
	public:
		Camera(GameObject* gameobject);

		void SetSubject(GameObject* gameobject);
		void SetTexturePos(GameObject* gameobject);

		void Update();
	};
}

#endif // !CAMERA_H_