#include "../agent.h"

namespace object
{
	Agent::Agent(GameObject* gameobject, std::vector<Vector2D> points)
		: GeometryObject(gameobject, points)
	{
		SetEntityType(GameEntityType::Agent);

		m_aistate = AgentState::Wandering;
		m_dead = false;

		m_turnobj.steps = 0;
		m_turnobj.left = 0;

		m_seenagent = NULL;
		m_targetpos = VEC2_ZERO;

		m_velocity = 0;
		m_turnspeed = 0;
		m_isturning = false;
		m_ismoving = false;

		set_randomtraits();
		set_traits();
	}

	Agent::~Agent()
	{}

	void Agent::TakeDamage(int damage)
	{
		// TODO : more rules for this
		m_aistate = AgentState::Fleeing;
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
			Agent* agent = static_cast<Agent*>(ent);
			m_seenagent  = agent;
			// mating checks
			bool is_mateable = check_mate(agent);

			// owo
			if (is_mateable)
			{
				m_targetpos = agent->Get2DPosition();
			}
			// enemy checks
			if (!is_mateable)
			{
				int agro = m_traits.agression;
				const auto& distsq = maths::GetDistanceBetweenPoints_sq(ent->Get2DPosition(), Get2DPosition());
				bool colourdistancecheck = maths::ColourDifference(m_traits.colour, agent->Colour())
					> 150.0 / (agro + 1);
				if (distsq < 5e3 * agro && agro > 3 && colourdistancecheck
					&& m_aistate != AgentState::Fleeing && m_aistate != AgentState::Mating)
				{
					m_aistate = AgentState::Attacking;
				}
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

	bool Agent::check_mate(Agent* mate)
	{
		// has to be different gender
		if (mate->Gender() == m_gender) 
		{ return false; }
		// colour has to be close
		double cdifference = maths::ColourDifference(m_traits.colour, mate->Colour());
		return cdifference < 50;
	}

	void Agent::set_randomtraits()
	{
		m_traits =
		{
			get_randomname(), // name
			get_randomcolour(), // colour

			maths::GetRandomFloat(1.0f, 3.0f), // walkspeed
			maths::GetRandomFloat(1.0f, 3.0f), // turnspeed
			maths::GetRandomInt(100, 500),	   // health 
			maths::GetRandomInt(750, 1500),    // stamina
			maths::GetRandomInt(5, 15),        // damage
			maths::GetRandomInt(0, 10)         // aggresion
		};
	}

	void Agent::set_traits()
	{
		m_gender	= maths::GetRandomInt(0, 1);
		m_agression = m_traits.agression;
		m_stamina   = m_traits.maxstamina;
		m_health    = m_traits.maxhealth;
		GetGeometry()->Colour(m_traits.colour);
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
		float yaw = (GetTransform().GetRotation() + m_turnspeed) * DEG_TO_RAD;

		Vector2D direction_vec2d  = { cosf(yaw), sinf(yaw) };
		Vector2D pos_change_vec2d = direction_vec2d * m_velocity;

		m_offset_pos	  = { pos_change_vec2d.x, pos_change_vec2d.y, 0 }; // TODO : this isnt good
		m_offset_rotation = { 0, 0, m_turnspeed };
	}

	void Agent::turnright()
	{
		m_turnspeed = fminf(m_traits.maxturnspeed, m_turnspeed + 0.5f);
		m_isturning = true;
	}

	void Agent::turnleft()
	{
		m_turnspeed = fmaxf(-m_traits.maxturnspeed, m_turnspeed - 0.5f);
		m_isturning = true;
	}

	void Agent::moveforward()
	{
		m_velocity = fminf(m_traits.maxwalkspeed, m_velocity + 0.5f);
		m_ismoving = true;
	}

	void Agent::movebackward()
	{
		m_velocity = fmaxf(-m_traits.maxwalkspeed, m_velocity - 0.5f);
		m_ismoving = true;
	}

	void Agent::rotate_topos(Vector2D pos)
	{
		float rotation = get_degtopos(pos);
		SetRotation(rotation);
	}

	float Agent::get_degtopos(Vector2D pos)
	{
		int ang = maths::GetAngleBetweenPoints({ GetPosition().x, GetPosition().y }, pos);
		maths::GetBoundedAngleDeg(ang);
		return (float)ang;
	}

	void Agent::move_towardtargetpos()
	{
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
			int agentrotation  = GetTransform().GetRotation();
			int targetrotation = get_degtopos(m_targetpos);

			float delta = (targetrotation - agentrotation + 540) % 360 - 180;

			delta < 0 ? turnleft() : turnright();
		}
		moveforward();
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

	void Agent::mate()
	{

	}

	void Agent::eat()
	{
		if (m_stamina > m_traits.maxstamina * 0.9)
		{ m_aistate = AgentState::Wandering; return; }

		// if is in food eat it
		Food* food = {};
		if (is_infood(food))
		{
			int eaten = food->Eat();
			m_health  = std::min(m_health + eaten, m_traits.maxhealth);
			m_stamina += eaten;
			return;
		}

		// see if food is in memory
		Vector2D mempos = get_memoryentitypos(GameEntityType::Food);
		if (mempos != VEC2_ZERO) // can remember
		{
			set_targetpos(mempos); 
			if (is_attargetpos(30))
			{
				forget(mempos);
			}
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
			// do damage based on spikeyness
			int damage = 15.0 / GetSpikyness();
			m_seenagent->TakeDamage(damage);
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
		if (m_stamina < m_traits.maxstamina - 500) 
		{ m_aistate = AgentState::Eating; }

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
		case AgentState::Mating:
			mate();
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

	std::string Agent::get_randomname()
	{
		std::vector<std::string> firstnames = file::GetLinesFromFile("firstnames.txt");
		std::vector<std::string> lastnames = file::GetLinesFromFile("lastnames.txt");
		return *maths::select_randomly(firstnames.begin(), firstnames.end())
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