#ifndef AGENT_H_
#define AGENT_H_

#include "../object/objects/geometry-object.h"

namespace object
{
	struct Turnobj {
		int   steps;
		bool  left;
	};

	enum class AgentState
	{
		Wandering,
		Attacking
	};

	class Agent : public GeometryObject
	{
	private:
		// brain
		Turnobj	   m_turnobj;
		AgentState m_aistate;
		Vector2D   m_mood; // happy/sad & fear/confidence

		// targets
		Vector2D		m_targetpos;
		GeometryObject*	m_targetentity;

		// movement
		const float MAX_VELOCITY  = 3.0f;
		const float MAX_TURNSPEED = 4.0f;
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
	public:
		Agent(GameObject* gameobject, int sides);

		// navigation
		void SetTargetpos(Vector2D pos);
		void SetTargetent(GeometryObject* ent);
		void Attack();
		void Wander();
		void SeenEnt(GeometryObject* ent);

		void Update();
	};
}

#endif // !AGENT_H_