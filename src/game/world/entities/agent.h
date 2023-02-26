#ifndef AGENT_H_
#define AGENT_H_

#include "../src/game/world/objects/geometry-object.h"
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
		std::string t_name;
		int t_food;
		int t_health;
		int t_damage;
		float t_maxvel;
		float t_maxturn;
		SDL_Color t_colour;

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
		void calc_transformoffsets();

		void  rotate_to_pos(Vector2D pos);
		float get_deg_to_pos(Vector2D pos);

		// movement
		void turnleft();
		void turnright();
		void moveforward();
		void movebackward();

		// TODO : move
		SDL_Color get_randomcolour();

		~Agent();
	public:
		Agent(GameObject* gameobject, int sides);

		inline std::string GetName()
		{
			return t_name;
		}

		inline int GetHealth()
		{
			return t_health;
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