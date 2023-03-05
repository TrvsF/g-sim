#ifndef AGENT_H_
#define AGENT_H_

#include "../src/game/world/objects/geometry-object.h"
#include "food.h"
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
		Fleeing,
		Eating
	};

	class Agent : public GeometryObject
	{
	private:
		// brain/stats
		Turnobj	   m_turnobj;
		AgentState m_aistate;
		Vector2D   m_mood; // happy/sad & fear/confidence
		int		   m_stamina;
		int		   m_health;
		bool       m_dead;

		// traits
		std::string t_name;
		int t_food;
		int t_maxhealth;
		int t_damage;
		float t_maxvel;
		float t_maxturn;
		SDL_Color t_colour;

		// settargets
		Vector2D	m_targetpos;
		GameObject*	m_targetobject;
		
		// memory
		Agent* m_seenagent;
		std::vector<GameObject*> m_collidedobjs;
		std::vector<std::pair<Vector2D, GameEntityType>> m_objectmemory;
		void add_objecttomemory(GameObject* object);
		void forget(Vector2D pos);
		Vector2D get_memoryentitypos(GameEntityType type);

		// movement util
		void do_brain();
		void do_friction();
		void calc_transformoffsets();
		void rotate_topos(Vector2D pos);
		float get_degtopos(Vector2D pos);

		// target util
		bool is_attargetpos(int radius);
		bool is_infood(Food*& food);
		Vector2D get_newtargetpos();

		// movement vars
		float m_velocity;
		float m_turnspeed;
		bool  m_isturning;
		bool  m_ismoving;

		// movement methods
		void turnleft();
		void turnright();
		void moveforward();
		void movebackward();
		void move_towardtargetpos();

		// navigation
		void check_targetpos();
		inline void set_targetpos(Vector2D pos)
		{ m_targetpos = pos; }
		inline void set_targetagent(Agent* agent)
		{ m_seenagent = agent; }

		// states
		void attack();
		void wander();
		void   flee();
		void	eat();

		// TODO : move
		void set_name();
		SDL_Color get_randomcolour();

		~Agent();
	public:
		Agent(GameObject* gameobject, int sides);
		Agent(GameObject* gameobject, std::vector<Vector2D> points);

		inline void AddCollidedObj(GameObject* obj)
		{ m_collidedobjs.push_back(obj); }

		inline bool IsDead()
		{ return m_dead; }

		void Die();
		void TakeDamage(int damage);
		void SeenEnt(GameObject* ent);

		void Update();

		// debug
		inline std::string GetName()
		{ return t_name; }

		inline int GetMaxHealth()
		{ return t_maxhealth; }

		inline int GetHealth()
		{ return m_health; }

		inline int GetStamina()
		{ return m_stamina; }
		
		std::string GetStateStr();
	};
}
#endif // !AGENT_H_