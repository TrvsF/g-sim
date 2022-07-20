#include "../updater.h"

#include "../src/object/component/object.h"

object::Object* game_obj = object::Object::Create(
	object::AABB::Create({ 0, 50, 0 }, { 25, 25, 0 }),
	object::Transform::Create({ 0, 50, 0 }, { 0, 0, 0 })
);

namespace physics
{
	Updater* Updater::s_instance = nullptr;

	Updater::Updater()
	{
	}

	Updater::~Updater()
	{
	}

	void Updater::Create()
	{
		if (!Updater::s_instance)
		{
			Updater::s_instance = new Updater();
		}
	}

	void Updater::Destroy()
	{
		SAFE_DELETE(s_instance);
	}

	void Updater::Tick()
	{

	}

}