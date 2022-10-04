#ifndef CAMERA_H_
#define CAMERA_H_

#include "../game-object.h"

namespace object
{
	class Camera : public GameObject
	{
	private:
		GameObject* m_subject;
	public:
		Camera(GameObject* gameobject);

		void SetSubject(GameObject* gameobject);
		void InterpTexture(GameObject* gameobject);

		void Update();

		void Tick();
	};
}

#endif // !CAMERA_H_