#ifndef AGENT_H_
#define AGENT_H_

#include "../src/game/object/objects/abstract/geometry-object.h"

/*
	TODO :
	chromosome/genome/sex
	- (see notes)
	eyes
	- have centeral eye point & cast a cone x deg either side of that
	- max range, cone size, placement
	brain
	- have random set of bits that controls how moves/interacts
	- maybe save last x bits for memeory?
	- cross-reference some(or all) to genome 
	- eg how fast, what to do when @ food, if violent etc
	limbs (maybe)
	- things that can be controlled to interact with world?
	- would also require brain to evolve to control? unless hard-coded:/
*/

namespace object
{
	class Agent : public GeometryObject
	{
	private:
		
	public:
		Agent(GameObject* gameobject, int sides);

		void Update();
	};
}

#endif // !AGENT_H_