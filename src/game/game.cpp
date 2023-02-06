#include "game.h"

namespace game
{
	Game::Game()
	{
		m_collision = new Collision(128);

		m_player = nullptr;
		m_camera = nullptr;
		m_consoletxt = nullptr;

		m_selected_obj = nullptr;
		m_level = nullptr;

		m_listener.listen<event::ePosChange>(std::bind(&Game::e_poschange, this, std::placeholders::_1));
	}

	void Game::e_poschange(const event::ePosChange& event)
	{
		m_player->SetPosition({event.pos.x, event.pos.y, 0});
	}

	void Game::OnMouseRelease(int mousebutton)
	{
		switch (mousebutton)
		{
		case 1:
			m_selected_obj = nullptr;
			break;
		}
	}

	void Game::OnMouseDown(int mousebutton, int x, int y)
	{
		// TODO : fix
		switch (mousebutton)
		{
		case 1:
			// if there is no selected object see if we can find one
			m_selected_obj = GetClickedObj(x, y);
			if (m_selected_obj == nullptr) { return; }
			// move the about around :D
			Vector3D pos = { x - m_selected_obj_offset.x, y - m_selected_obj_offset.y, 0 };
			m_selected_obj->SetPosition(pos);
		}
	}

	// TODO : compleatly redone with getting texture pos instead of object pos - shouldnt be here as this holds OBJECTS
	void Game::OnMouseClick(int mousebutton, int x, int y)
	{
		switch (mousebutton)
		{
		case 1: // m1
		{
		}
		break;
		case 2: // mm
		{
		}
		break;
		case 4: // m2
		{
			object::GameObject* obj = GetClickedObj(x, y);
			if (obj == nullptr && m_camera->GetSubject() != m_player)
			{
				m_camera->SetSubject(m_player);
				return;
			}
			m_camera->SetSubject(obj);
		}
		break;
		}
	}

	object::GameObject* Game::GetClickedObj(int x, int y)
	{
		for (object::GameObject* object : m_gameworld_objects)
		{
			// TODO : make this faster/not care about objects not on screen
			Vector2D screenpos;
			if (object->GetObjType() == object::GameObjectType::Texture)
			{
				object::TextureObject* screenobj = static_cast<object::TextureObject*> (object);
				screenpos = screenobj->GetTexture()->Pos();
			}
			if (object->GetObjType() == object::GameObjectType::Geometry)
			{
				object::GeometryObject* screenobj = static_cast<object::GeometryObject*> (object);
				screenpos = screenobj->GetGeometry()->Pos();
			}
			object::AABB aabb = object::AABB::Create({ screenpos.x, screenpos.y, 0 }, object->GetSize());

			if (aabb.IntersectsPoint(x, y))
			{
				m_selected_obj = object;
				m_selected_obj_offset = { x - object->GetPosition().x, y - object->GetPosition().y };
				return object;
			}
		}
		return nullptr;
	}

	void Game::Start()
	{
		// SETUP CAMERA AND PLAYER OBJECTS
		object::GameObject* playerobj = object::GameObject::Create(
			{  200.0f,  200.0f,  0.0f  },
			{  0.0f,    0.0f,    0.0f  }, 
			{  32.0f,   32.0f,   32.0f }
		);

		m_player = new object::Player(playerobj, "player");
		AddGameObject(m_player);
		// m_gameworld_objects.push_back(m_player); // TODO : MAKE SURE THIS IS ALWAYS AT THE FRONT (z indexing?)

		object::GameObject* cameraobj = object::GameObject::Create(
			{ 0.0f,   0.0f,   0.0f },
			{ 0.0f,   0.0f,   0.0f },
			{ 300.0f, 300.0f, 300.0f }
		);

		m_camera = new object::Camera(cameraobj);
		m_camera->SetSubject(m_player);

		// debug
		object::GameObject* miscagent = object::GameObject::Create(
			{ 100.0f,  400.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 32.0f,   32.0f,   32.0f }
		);
		AddGameObject(new object::Agent(miscagent, 4)); // TODO : Scale BB with tri size

		object::GameObject* food = object::GameObject::Create(
			{ 600.0f,  400.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 64.0f,   64.0f,   64.0f }
		);
		AddGameObject(new object::Food(food, "food"));

		object::GameObject* triman = object::GameObject::Create(
			{ 150.0f,   0.0f,    0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::GameObject* triman2 = object::GameObject::Create(
			{ 400.0f,   400.0f,  0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::GameObject* triman3 = object::GameObject::Create(
			{ 250.0f,   250.0f,  0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::GameObject* triman4 = object::GameObject::Create(
			{ 50.0f,   50.0f,   0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 64.0f,   64.0f,   64.0f }
		);
		srand(time(NULL)); // move me
		AddGameObject(new object::GeometryObject(triman,  4));
		AddGameObject(new object::GeometryObject(triman2, 5));
		AddGameObject(new object::GeometryObject(triman3, 4));
		AddGameObject(new object::GeometryObject(triman4, 5));

		object::GameObject* textobj = object::GameObject::Create(
			{ 0.0f,    0.0f,    0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 0.0f,    0.0f,    0.0f }
		);
		// TODO : check for is text obj to change text etc
		m_consoletxt = new object::TextObject(textobj, "HenryBlue-Regular", "hello georgia!", { 0, 255, 0 });
		m_consoletxt->GetTexture()->Active(false);
		AddGameObject(m_consoletxt);
	}

	// entities -> camera
	void Game::Tick()
	{
		// tick/collision objects
		for (object::GameObject* gameworldobject : m_gameworld_objects)
		{
			m_collision->CheckCollisionObj(gameworldobject);
			m_collision->DoCollision();
			gameworldobject->Tick();
		}
		// camera
		m_camera->Tick();
		// console
		m_consoletxt->GetTexture()->Active(console::ACTIVE);
		m_consoletxt->SetText(console::m_inputstr);
		// update what camera sees
		for (object::GameObject* gameworldobject : m_gameworld_objects)
		{
			if (gameworldobject == m_consoletxt) { continue; } // hack for console text
			m_camera->SetTexturePos(gameworldobject);
		}
	}
}