#include "../player.h"

namespace object
{
	Player::Player(GameObject* gameobject, const char* textureid)
		: TextureObject(gameobject, textureid)
	{
		m_inputvector = VEC2_ZERO;
	}

	void Player::Update()
	{
		/*
		float yaw = GetTransform().GetRotation().z;
		Vector2D direction_vec2d = { (float)cosf(yaw), (float)sin(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_inputvector;
		*/

		m_offset_pos = { m_inputvector.x, m_inputvector.y, 0.0f };
		
		GetTexture()->OffsetPos(m_inputvector);

		m_inputvector = VEC2_ZERO;
	}
}