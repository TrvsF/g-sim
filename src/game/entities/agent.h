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
		int		 m_agression;

		// navigation
		Vector2D m_targetpos;

		// movement
		const float MAX_VELOCITY  = 3.0f;
		const float MAX_TURNSPEED = 4.0f;
		float m_velocity;
		float m_turnspeed;
		bool  m_isturning;
		bool  m_ismoving;
		void do_friction();
		void calc_offsetrotation();
		void calc_offsetpos();
	public:
		Agent(GameObject* gameobject, int sides);

		// navigation
		void  SetTargetpos(Vector2D pos);
		void  rotate_to_targetpos();
		float get_deg_to_targetpos();
		void  Wander();

		// movement
		void TurnLeft();
		void TurnRight();
		void MoveForward();
		void MoveBackward();

		void Update();
	};
}

#endif // !AGENT_H_