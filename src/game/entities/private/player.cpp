#include "../player.h"

namespace object
{
	Player::Player(GameObject* gameobject, const char* textureid)
		: TextureObject(gameobject, textureid)
	{
		SetEntityType(GameEntityType::Player);
		m_inputvector = VEC2_ZERO;
	}

	void Player::Update()
	{
		/*
		float yaw = GetTransform().GetRotation().z;
		Vector2D direction_vec2d = { (float)cosf(yaw), (float)sin(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_inputvector;
		*/

		maths::GetAngleBetweenPoints({ GetTransform().GetPosition().x, GetTransform().GetPosition().y },
			{ GetTransform().GetPosition().x + 100, GetTransform().GetPosition().y -50 });

		m_offset_pos = { m_inputvector.x, m_inputvector.y, 0.0f };
		m_inputvector = VEC2_ZERO;
	}
}