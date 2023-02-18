#ifndef AI_H_
#define AI_H_

#include "../game.h"
#include "../entities/agent.h"
#include "../object/game-object.h"

namespace ai
{
	class AI
	{
	private:
		AI() = default;
		virtual ~AI() = default;

		std::vector<object::Agent*> getagents();
	public:
		static AI& SharedInstace() { static AI ai; return ai; }

		void Tick();
	};
}

#endif