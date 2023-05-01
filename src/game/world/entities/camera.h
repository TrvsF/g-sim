#ifndef CAMERA_H_
#define CAMERA_H_

#include "../src/game/world/game-object.h"
#include "../src/game/world/objects/texture-object.h"
#include "../src/game/world/objects/geometry-object.h"
#include "../src/game/world/component/geometry.h"
#include "../src/game/world/component/texture.h"

namespace object
{
	class Camera : public GameObject
	{
	private:
		GameObject*				m_subject;
		Vector2D				m_offset;

		std::vector<Texture*>	m_textureobjs;
		Vector2D				m_screensize;
		Vector2D				m_local_offset_pos;
	public:
		Camera(GameObject* gameobject);

		inline GameObject* GetSubject()
		{
			return m_subject;
		}
		void SetSubject(GameObject* gameobject);
		void SetTexturePos(GameObject* gameobject);
		
		inline void Offset(Vector2D offset) 
		{ GetTransform().OffsetPosition({ offset.x, offset.y }); }

		inline const Vector2D GetOffsetpos()
		{
			return m_local_offset_pos;
		}

		void Update();
	};
}

#endif // !CAMERA_H_