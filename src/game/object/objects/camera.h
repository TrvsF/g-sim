#ifndef CAMERA_H_
#define CAMERA_H_

#include "../game-object.h"
#include "abs/texture-object.h"
#include "../component/texture.h"

namespace object
{
	class Camera : public GameObject
	{
	private:
		GameObject*				m_subject;
		std::vector<Texture*>	m_textureobjs;
		Vector2D				m_interp_pos;
		Vector2D				m_screensize;
	public:
		Camera(GameObject* gameobject);

		void SetSubject(GameObject* gameobject);
		void SetTexturePos(GameObject* gameobject);

		void Tick();
	};
}

#endif // !CAMERA_H_