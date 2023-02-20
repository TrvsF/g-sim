#include "../agent.h"

namespace object
{
	Agent::Agent(GameObject* gameobject, int sides)
		: GeometryObject(gameobject, sides)
	{
		SetEntityType(GameEntityType::Agent);

		m_aistate   = AgentState::Wandering;
		m_mood		= VEC2_ZERO;
		m_dead		= false;

		// TODO : set by genome
		set_name();
		m_maxvel  = maths::GetRandomFloat(1.0f, 3.0f);
		m_maxturn = maths::GetRandomFloat(1.0f, 3.0f);
		m_health  = maths::GetRandomInt(70, 250);
		m_maincolour = {}; // TODO : sync to geometry
		m_secondarycolour = {};

		m_turnobj.steps = 0;
		m_turnobj.left  = 0;

		m_targetentity = NULL;
		m_targetpos	   = {500, 500};

		m_velocity  = 0;
		m_turnspeed = 0;
		m_isturning = false;
		m_ismoving  = false;
	}

	Agent::~Agent()
	{}

	void Agent::set_name()
	{
		std::vector<std::string> names = file::GetLinesFromFile("firstnames.txt");
		m_name = *maths::select_randomly(names.begin(), names.end());
	}

	void Agent::do_friction()
	{
		if (!m_ismoving)
		{
			m_velocity /= 1.1f;
			if (fabsf(m_velocity) < 0.05f) { m_velocity = 0; }
		}

		if (!m_isturning)
		{
			m_turnspeed /= 1.1f;
			if (fabsf(m_turnspeed) < 0.05f) { m_turnspeed = 0; }
		}

		m_isturning = false;
		m_ismoving  = false;
	}

	void Agent::calc_offsetpos()
	{
		float yaw = (GetTransform().GetRotation().z + m_turnspeed) * DEG_TO_RAD;

		Vector2D direction_vec2d  = { cosf(yaw), sinf(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_velocity;

		m_offset_pos	  = { pos_change_vec2d.x, pos_change_vec2d.y, 0 }; // TODO : this isnt good
		m_offset_rotation = { 0, 0, m_turnspeed };
	}

	void Agent::turnright()
	{
		m_turnspeed = fminf(m_maxturn, m_turnspeed + 0.5f);
		m_isturning = true;
	}

	void Agent::turnleft()
	{
		m_turnspeed = fmaxf(-m_maxturn, m_turnspeed - 0.5f);
		m_isturning = true;
	}

	void Agent::moveforward()
	{
		m_velocity = fminf(m_maxvel, m_velocity + 0.5f);
		m_ismoving = true;
	}

	void Agent::movebackward()
	{
		m_velocity = fmaxf(-m_maxvel, m_velocity - 0.5f);
		m_ismoving = true;
	}

	void Agent::SetTargetpos(Vector2D pos)
	{
		m_targetpos = pos;
	}

	void Agent::SetTargetent(Agent* ent)
	{
		m_targetentity = ent;
	}

	void Agent::rotate_to_pos(Vector2D pos)
	{
		float rotation = get_deg_to_pos(pos);
		SetRotation(rotation);
	}

	float Agent::get_deg_to_pos(Vector2D pos)
	{
		int ang = maths::GetAngleBetweenPoints({ GetPosition().x, GetPosition().y }, { pos });
		maths::GetBoundedAngleDeg(ang);
		return (float)ang;
	}

	void Agent::DoDamage(int damage)
	{
		m_health = std::max(m_health - damage, 0);
		if (m_health <= 0 && !m_dead) { Kill(); }
	}

	void Agent::Kill()
	{
		// GetGeometry()->Active(false);
		bus->postpone(event::eAgentDeath { this });
		bus->process();
		m_dead = true;
	}

	void Agent::SeenEnt(Agent* ent)
	{
		m_mood.y++;
		if (m_mood.y > 5 && m_aistate == AgentState::Wandering)
		{
			m_aistate	   = AgentState::Attacking;
			m_targetentity = ent;
		}
	}

	void Agent::Wander()
	{
		moveforward();

		// 1/250 chance to create new turnobj
		if (maths::GetRandomInt(0, 249) == 0)
		{
			m_turnobj.left  = maths::GetRandomInt(0, 1);
			m_turnobj.steps = maths::GetRandomInt(0, 50);
		}

		// is object has steps then turn in that dir, if not turn toward the goal
		if (m_turnobj.steps != 0)
		{
			m_turnobj.left ? turnleft() : turnright();
			m_turnobj.steps--;
		}
		else 
		{
			float r = GetTransform().GetRotation().z - get_deg_to_pos(m_targetpos);
			r > 0 ? turnleft() : turnright();
		}
	}

	void Agent::Attack()
	{
		// TODO : fix bad pointer
		if (m_targetentity == NULL)
		{ m_aistate = AgentState::Wandering; return; }

		rotate_to_pos({ m_targetentity->GetPosition().x, m_targetentity->GetPosition().y });
		moveforward();
		
		// if is inside target
		bool iscollided = false;
		for (const auto& object : m_collidedobjs)
		{
			if (object->GetEntityType() == GameEntityType::Agent)
			{
				Agent* entity = dynamic_cast<Agent*>(object);
				if (entity == m_targetentity) { iscollided = true; break; }
			}
		}

		if (iscollided)
		{
			m_targetentity->DoDamage(10);
			if (m_targetentity->IsDead()) 
			{
				m_targetentity = NULL;
				m_aistate = AgentState::Wandering;
			}
		}
	}

	void Agent::Flee()
	{
		if (m_targetentity == NULL)
		{ m_aistate = AgentState::Wandering; return; }

		rotate_to_pos({ m_targetentity->GetPosition().x, m_targetentity->GetPosition().y });
		movebackward();
	}

	void Agent::do_brain()
	{
		switch (m_aistate)
		{
		case AgentState::Wandering:
			Wander();
			break;
		case AgentState::Attacking:
			Attack();
			break;
		case AgentState::Fleeing:
			Flee();
			break;
		default:
			break;
		}
		m_collidedobjs.clear();
	}

	void Agent::Update()
	{
		do_brain();
		do_friction();
		calc_offsetpos();
	}
}