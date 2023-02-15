#ifndef PLAYER_H_
#define PLAYER_H_

#include "../object/objects/texture-object.h"

namespace object
{
	class Player : public TextureObject
	{
	private:
		int m_velocity;
		int m_rotation;

		void reset_tickvars()
		{
			m_velocity = 0;
			m_rotation = 0;
		}
	public:
		Player(GameObject* gameobject, const char* textureid);

		void Update();

		void MoveUp()		{ m_velocity += 5; }
		void MoveDown()		{ m_velocity -= 2; }
		void MoveLeft()		{ m_rotation -= 3; }
		void MoveRight()	{ m_rotation += 3; }
	};
}

#endif // !PLAYER_H_