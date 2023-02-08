#include "../agent.h"

namespace object
{
	Agent::Agent(GameObject* gameobject, int sides)
		: GeometryObject(gameobject, sides)
	{
		SetEntityType(GameEntityType::Agent);
		m_velocity = 0;
		m_ismoving = false;
	}

	void Agent::do_friction()
	{
		if (!m_ismoving)
		{
			m_velocity /= 1.1f;
			if (fabsf(m_velocity) < 0.1f) { m_velocity = 0; }
		}
		m_ismoving = false;
	}

	void Agent::calc_offsetpos()
	{
		float yaw = GetTransform().GetRotation().z * DEG_TO_RAD;

		Vector2D direction_vec2d = { cosf(yaw), sinf(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_velocity;

		m_offset_pos = { pos_change_vec2d.x, pos_change_vec2d.y };
	}

	void Agent::MoveForward()
	{
		m_velocity = fminf(MAX_VELOCITY, m_velocity + 0.5f);
		m_ismoving = true;
	}

	void Agent::MoveBackward()
	{
		m_velocity = fmaxf(-MAX_VELOCITY, m_velocity - 0.5f);
		m_ismoving = true;
	}

	void Agent::Update()
	{
		MoveForward();
		do_friction();
		calc_offsetpos();
	}
}