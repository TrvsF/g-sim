#ifndef CAMERA_H_
#define CAMERA_H_

#include "../game-object.h"
#include "../component/texture.h"

namespace object
{
	class Camera : public GameObject
	{
	private:
		GameObject* m_subject;
		std::vector<Texture*> m_textureobjs;
	public:
		Camera(GameObject* gameobject);

		void SetSubject(GameObject* gameobject);
		void AddTextureobj(Texture* textureobject);

		void Update();
	};
}

#endif // !CAMERA_H_