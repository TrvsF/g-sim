#ifndef AGENT_H_
#define AGENT_H_

#include "abs/texture-object.h"

namespace object
{
	class Agent : public TextureObject
	{
	private:
		
	public:
		Agent(GameObject* gameobject, const char* textureid);

		void Update();
	};
}

#endif // !AGENT_H_