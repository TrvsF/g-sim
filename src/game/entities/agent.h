#ifndef AGENT_H_
#define AGENT_H_

#include "../object/objects/geometry-object.h"
#include "../src/util/file.h"

namespace object
{
	struct Turnobj {
		int   steps;
		bool  left;
	};

	enum class AgentState
	{
		Wandering,
		Attacking,
		Fleeing
	};

	class Agent : public GeometryObject
	{
	private:
		// brain/stats
		Turnobj	   m_turnobj;
		AgentState m_aistate;
		Vector2D   m_mood; // happy/sad & fear/confidence
		bool       m_dead;

		// traits
		std::string m_name;
		int m_food;
		int m_health;
		int m_damage;
		float m_maxvel;
		float m_maxturn;
		SDL_Color m_maincolour;
		SDL_Color m_secondarycolour;
		void set_name();

		// targets
		Vector2D m_targetpos;
		Agent*	 m_targetentity;
		std::vector<GameObject*> m_collidedobjs;

		// movement
		float m_velocity;
		float m_turnspeed;
		bool  m_isturning;
		bool  m_ismoving;

		void do_brain();
		void do_friction();
		void calc_offsetrotation();
		void calc_offsetpos();

		void  rotate_to_pos(Vector2D pos);
		float get_deg_to_pos(Vector2D pos);

		// movement
		void turnleft();
		void turnright();
		void moveforward();
		void movebackward();

		~Agent();
	public:
		Agent(GameObject* gameobject, int sides);

		inline std::string GetName()
		{
			return m_name;
		}

		inline void AddCollidedObj(object::GameObject* obj)
		{
			m_collidedobjs.push_back(obj);
		}

		// navigation
		void SetTargetpos(Vector2D pos);
		void SetTargetent(Agent*   ent);
		void Attack();
		void Wander();
		void   Flee();
		void SeenEnt(GeometryObject* ent);
		void SeenEnt(Agent* ent);

		inline bool IsDead() { return m_dead; }
		void Kill();
		void DoDamage(int damage);

		void Update();
	};
}

#endif // !AGENT_H_