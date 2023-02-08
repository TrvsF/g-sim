#ifndef AGENT_H_
#define AGENT_H_

#include "../object/objects/geometry-object.h"

namespace object
{
	class Agent : public GeometryObject
	{
	private:
		// movement
		const float MAX_VELOCITY  = 5.0f;
		const float MAX_TURNSPEED = 4.0f;
		float m_velocity;
		bool  m_ismoving;

		void do_friction();
		void calc_offsetrotation();
		void calc_offsetpos();
	public:
		Agent(GameObject* gameobject, int sides);

		void MoveForward();
		void MoveBackward();

		void Update();
	};
}

#endif // !AGENT_H_