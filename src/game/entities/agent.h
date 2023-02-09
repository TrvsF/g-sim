#ifndef AGENT_H_
#define AGENT_H_

#include "../object/objects/geometry-object.h"

namespace object
{
	class Agent : public GeometryObject
	{
	private:
		// navigation
		Vector2D m_targetpos;

		// movement
		const float MAX_VELOCITY  = 5.0f;
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

		// nivigation
		void SetTargetpos(Vector2D pos);
		void MoveToTargetPos();

		// movement
		void TurnLeft();
		void TurnRight();
		void MoveForward();
		void MoveBackward();

		void Update();
	};
}

#endif // !AGENT_H_