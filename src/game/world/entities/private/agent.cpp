#include "../agent.h"

namespace object
{
	Agent::Agent(GameObject* gameobject, int sides)
		: GeometryObject(gameobject, sides)
	{
		SetEntityType(GameEntityType::Agent);

		// TODO : set by genome
		// - gneome will have 2 chromosomes
		// - A dicates solely the geometry object
		// - B will determine personality triats (agression, etc)
		// - below vars are made up of either B or B/A(mix)
		t_maxvel  = maths::GetRandomFloat(1.0f, 3.0f);
		t_maxturn = maths::GetRandomFloat(1.0f, 3.0f);
		t_maxhealth  = maths::GetRandomInt(70, 250);
		t_food    = maths::GetRandomInt(-10, 10) + t_maxhealth;
		t_damage  = maths::GetRandomInt(5, 15);
		t_colour  = get_randomcolour();
		GetGeometry()->Colour(t_colour);
		set_name();
		// --------------------------

		m_aistate = AgentState::Wandering;
		m_mood = VEC2_ZERO;
		m_dead = false;
		m_stamina = 5000;
		m_health = t_maxhealth;

		m_turnobj.steps = 0;
		m_turnobj.left  = 0;

		m_seenagent = NULL;
		m_targetpos	= VEC2_ZERO;

		m_velocity  = 0;
		m_turnspeed = 0;
		m_isturning = false;
		m_ismoving  = false;
	}

	Agent::Agent(GameObject* gameobject, std::vector<Vector2D> points)
		: GeometryObject(gameobject, points)
	{
		SetEntityType(GameEntityType::Agent);

		// TODO : set by genome
		// - gneome will have 2 chromosomes
		// - A dicates solely the geometry object
		// - B will determine personality triats (agression, etc)
		// - below vars are made up of either B or B/A(mix)
		t_maxvel = maths::GetRandomFloat(1.0f, 3.0f);
		t_maxturn = maths::GetRandomFloat(1.0f, 3.0f);
		t_maxhealth = maths::GetRandomInt(70, 250);
		t_food = maths::GetRandomInt(-10, 10) + t_maxhealth;
		t_damage = maths::GetRandomInt(5, 15);
		t_colour = get_randomcolour();
		GetGeometry()->Colour(t_colour);
		set_name();
		// --------------------------

		m_aistate = AgentState::Wandering;
		m_mood = VEC2_ZERO;
		m_dead = false;
		m_stamina = 5000;
		m_health = t_maxhealth;

		m_turnobj.steps = 0;
		m_turnobj.left = 0;

		m_seenagent = NULL;
		m_targetpos = VEC2_ZERO;

		m_velocity = 0;
		m_turnspeed = 0;
		m_isturning = false;
		m_ismoving = false;
	}

	Agent::~Agent()
	{}

	void Agent::TakeDamage(int damage)
	{
		m_health = std::max(m_health - damage, 0);
		if (m_health <= 0 && !m_dead) { Die(); }
	}

	void Agent::Die()
	{
		console::bus->postpone(event::eObjectDeath { this });
		console::bus->process();
		GetGeometry()->Active(false);
		m_dead = true;
	}

	void Agent::SeenEnt(GameObject* ent)
	{
		if (ent->GetEntityType() == GameEntityType::Agent)
		{
			m_mood.y++;
			if (m_mood.y > 5)
			{
				m_aistate = AgentState::Attacking;
				m_seenagent = static_cast<Agent*>(ent);
			}
		}
		if (ent->GetEntityType() == GameEntityType::Food)
		{
			for (const auto& memory : m_objectmemory)
			{
				if (memory.first == ent->Get2DPosition())
				{
					return;
				}
			}
			add_objecttomemory(ent);
		}
	}

	void Agent::add_objecttomemory(GameObject* object)
	{
		Vector2D pos = object->Get2DPosition();
		GameEntityType type = object->GetEntityType();
		m_objectmemory.push_back({pos, type });
	}

	Vector2D Agent::get_memoryentitypos(GameEntityType type)
	{
		for (const auto& pair : m_objectmemory)
		{
			if (pair.second == type)
			{ return pair.first; }
		}
		return VEC2_ZERO;
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

	void Agent::calc_transformoffsets()
	{
		float yaw = (GetTransform().GetRotation().z + m_turnspeed) * DEG_TO_RAD;

		Vector2D direction_vec2d  = { cosf(yaw), sinf(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_velocity;

		m_offset_pos	  = { pos_change_vec2d.x, pos_change_vec2d.y, 0 }; // TODO : this isnt good
		m_offset_rotation = { 0, 0, m_turnspeed };
	}

	void Agent::turnright()
	{
		m_turnspeed = fminf(t_maxturn, m_turnspeed + 0.5f);
		m_isturning = true;
	}

	void Agent::turnleft()
	{
		m_turnspeed = fmaxf(-t_maxturn, m_turnspeed - 0.5f);
		m_isturning = true;
	}

	void Agent::moveforward()
	{
		m_velocity = fminf(t_maxvel, m_velocity + 0.5f);
		m_ismoving = true;
	}

	void Agent::movebackward()
	{
		m_velocity = fmaxf(-t_maxvel, m_velocity - 0.5f);
		m_ismoving = true;
	}

	void Agent::rotate_topos(Vector2D pos)
	{
		float rotation = get_degtopos(pos);
		SetRotation(rotation);
	}

	float Agent::get_degtopos(Vector2D pos)
	{
		int ang = maths::GetAngleBetweenPoints({ GetPosition().x, GetPosition().y }, { pos });
		maths::GetBoundedAngleDeg(ang);
		return (float)ang;
	}

	void Agent::move_towardtargetpos()
	{
		moveforward();

		// 1/250 chance to create new turnobj (sim random wondering)
		if (maths::GetRandomInt(0, 249) == 0 && m_aistate != AgentState::Eating)
		{
			m_turnobj.left = maths::GetRandomInt(0, 1);
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
			float r = GetTransform().GetRotation().z - get_degtopos(m_targetpos);
			r > 0 ? turnleft() : turnright();
		}
	}

	Vector2D Agent::get_newtargetpos()
	{
		// TODO : offset by 'adventureous' trait?
		Vector2D vec = Get2DPosition();
		vec += {(float)maths::GetRandomInt(-600, 600), (float)maths::GetRandomInt(-600, 600)};
		return vec;
	}

	bool Agent::is_attargetpos(int radius)
	{
		return maths::IsPointInsideOfRadius(Get2DPosition(), m_targetpos, radius);
	}

	bool Agent::is_infood(Food*& food)
	{
		for (const auto& object : m_collidedobjs)
		{
			if (object->GetEntityType() == GameEntityType::Food)
			{
				food = static_cast<Food*> (object);
				return true;
			}
		}
		return false;
	}

	void Agent::forget(Vector2D pos)
	{
		std::vector<std::pair<Vector2D, GameEntityType>>::iterator it = m_objectmemory.begin();
		while (it != m_objectmemory.end())
		{
			if ((*it).first == pos)
			{
				it = m_objectmemory.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void Agent::check_targetpos()
	{
		if (m_targetpos == VEC2_ZERO || is_attargetpos(50))
		{
			set_targetpos(get_newtargetpos());
		}
	}

	void Agent::wander()
	{
		check_targetpos();
		move_towardtargetpos();
	}

	void Agent::eat()
	{
		if (m_stamina > 5000)
		{ m_aistate = AgentState::Wandering; return; }

		// if is in food eat it
		Food* food = {};
		if (is_infood(food))
		{
			int eaten = food->Eat();
			m_health  = std::min(m_health + eaten, t_maxhealth);
			m_stamina += eaten;
			return;
		}

		// see if food is in memory
		Vector2D mempos = get_memoryentitypos(GameEntityType::Food);
		if (mempos != VEC2_ZERO) // can remember
		{
			set_targetpos(mempos); 
		}
		else
		{
			check_targetpos();
		}
		move_towardtargetpos();
	}

	void Agent::attack()
	{
		if (m_seenagent == NULL)
		{ m_aistate = AgentState::Wandering; return; }

		// move towards the target
		rotate_topos({ m_seenagent->GetPosition().x, m_seenagent->GetPosition().y });
		moveforward();
		
		// if is inside target
		bool iscollided = false;
		for (const auto& object : m_collidedobjs)
		{
			if (object->GetEntityType() == GameEntityType::Agent)
			{
				Agent* entity = dynamic_cast<Agent*>(object);
				if (entity == m_seenagent) { iscollided = true; break; }
			}
		}
		if (iscollided)
		{
			// do damage
			m_seenagent->TakeDamage(10);
			if (m_seenagent->IsDead()) 
			{
				// if dead, act like nothing happened
				m_seenagent = NULL;
				m_aistate = AgentState::Wandering;
			}
		}
	}

	void Agent::flee()
	{
		if (m_seenagent == NULL)
		{ m_aistate = AgentState::Wandering; return; }

		// face away from 
		rotate_topos(Vector2D{ m_seenagent->GetPosition().x, m_seenagent->GetPosition().y }
		+ 180.0f);
		moveforward();
	}

	void Agent::do_brain()
	{
		switch (m_aistate)
		{
		case AgentState::Wandering:
			wander();
			break;
		case AgentState::Attacking:
			attack();
			break;
		case AgentState::Fleeing:
			flee();
			break;
		case AgentState::Eating:
			eat();
			break;
		default:
			break;
		}
		m_seenagent = NULL;
		m_collidedobjs.clear();
	}

	void Agent::Update()
	{
		
		do_brain();
		// TODO : move
		if (m_stamina < 0) { Die(); }
		m_stamina--;
		if (m_stamina < 4500) { m_aistate = AgentState::Eating; }
		// transformations
		do_friction();
		calc_transformoffsets();
		
	}

	// debug

	std::string Agent::GetStateStr()
	{
		switch (m_aistate)
		{
		case AgentState::Wandering:
			return "wandering";
		case AgentState::Attacking:
			return "attacking";
		case AgentState::Fleeing:
			return "fleeing";
		case AgentState::Eating:
			return "eating";
		}
		return "";
	}

	void Agent::set_name()
	{
		std::vector<std::string> firstnames = file::GetLinesFromFile("firstnames.txt");
		std::vector<std::string> lastnames = file::GetLinesFromFile("lastnames.txt");
		t_name = *maths::select_randomly(firstnames.begin(), firstnames.end())
			+ "." + *maths::select_randomly(lastnames.begin(), lastnames.end());
	}

	SDL_Color Agent::get_randomcolour()
	{
		unsigned char r = maths::GetRandomInt(0, 255);
		unsigned char g = maths::GetRandomInt(0, 255);
		unsigned char b = maths::GetRandomInt(0, 255);
		return { r, g, b };
	}
}