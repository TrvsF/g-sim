#ifndef AGENT_H_
#define AGENT_H_

#include "../src/game/world/objects/geometry-object.h"
#include "food.h"
#include "../src/util/file.h"

namespace object
{
	struct Turnobj 
	{
		int   steps;
		bool  left;
	};

	struct Traits
	{
		std::string name; // ent name
		SDL_Color colour; // ent colour

		float maxwalkspeed; // 1-5
		float maxturnspeed; // 1-5
		int maxhealth;      // 50 - 500     [based too on size]
		int maxstamina;     // 1000 - 10000 [based too on size]
		int maxdamage;		// 5 - 25
		int agression;		// 0 - 10
	};

	enum class AgentState
	{
		Wandering,
		Attacking,
		Fleeing,
		Eating,
		Mating
	};

	class Agent : public GeometryObject
	{
	private:
		// brain/stats
		Turnobj	   m_turnobj;
		AgentState m_aistate;
		int		   m_agression;
		int		   m_stamina;
		int		   m_health;
		bool       m_dead;

		// genes
		std::string g_genome;

		// traits
		Traits m_traits;
		void set_randomtraits();
		void set_traits();
		
		// memory/targets
		Vector2D	m_targetpos;
		Agent* m_seenagent;

		std::vector<GameObject*> m_collidedobjs;
		std::vector<std::pair<Vector2D, GameEntityType>> m_objectmemory;

		void forget(Vector2D pos);
		void add_objecttomemory(GameObject* object);
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
		std::string get_randomname();
		SDL_Color get_randomcolour();

		~Agent();
	public:
		Agent(GameObject* gameobject);
		Agent(GameObject* gameobject, int sides);
		Agent(GameObject* gameobject, std::vector<Vector2D> points);

		inline void AddCollidedObj(GameObject* obj)
		{ m_collidedobjs.push_back(obj); }

		inline bool IsDead()
		{ return m_dead; }

		inline void SetGenome(std::string genome) 
		{ g_genome = genome; }
		inline std::string GetGenome() 
		{ return g_genome; }

		inline void SetTraits(Traits traits)
		{ m_traits = traits; }

		void Die();
		void TakeDamage(int damage);
		void SeenEnt(GameObject* ent);

		void Update();

		// debug
		inline std::string GetName()
		{ return m_traits.name; }
		
		inline int GetHealth()
		{ return m_health; }
		inline int GetMaxHealth()
		{ return m_traits.maxhealth; }

		inline int GetStamina()
		{ return m_stamina; }
		inline int GetMaxStamina()
		{ return m_traits.maxstamina; }
		
		std::string GetStateStr();
		// ------
	};
}
#endif // !AGENT_H_