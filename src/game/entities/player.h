#ifndef PLAYER_H_
#define PLAYER_H_

#include "../object/objects/texture-object.h"

namespace object
{
	class Player : public TextureObject
	{
	private:
		Vector2D m_inputvector;
	public:
		Player(GameObject* gameobject, const char* textureid);

		void Update();

		void MoveUp()		{ m_inputvector += { 0, -1 }; }
		void MoveDown()		{ m_inputvector += { 0,  1 }; }
		void MoveLeft()		{ m_inputvector += { -1, 0 }; }
		void MoveRight()	{ m_inputvector += {  1, 0 }; }
	};
}

#endif // !PLAYER_H_