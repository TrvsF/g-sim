#include "../updater.h"

#include "../src/game/object/component/object.h"

object::Object* game_obj = object::Object::Create(
	object::AABB::Create({ 0, 50, 0 }, { 25, 25, 0 }),
	object::Transform::Create({ 0, 50, 0 }, { 0, 0, 0 })
);

namespace updater
{
	Updater* Updater::s_instance = nullptr;

	Updater::Updater()
	{
		m_input			= new Input();
		m_controller	= new Controller(m_input);
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
		// must be first
		m_input->Tick();
		m_controller->CheckInputs();

		
		// must be last
		m_input->LateTick();
	}

}