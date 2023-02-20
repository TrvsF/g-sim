#include "game.h"

namespace game
{
	Game::Game()
	{
		m_collision = new Collision(128);

		m_player = nullptr;
		m_camera = nullptr;
		m_consoletxt = nullptr;
		m_coords     = nullptr;

		m_selected_obj = nullptr;

		m_listener.listen<event::ePosChange> (std::bind(&Game::e_poschange,  this, std::placeholders::_1));
		m_listener.listen<event::eAgentDeath>(std::bind(&Game::e_agentdeath, this, std::placeholders::_1));
	}

	void Game::e_poschange(const event::ePosChange& event)
	{
		m_player->SetPosition({event.pos.x, event.pos.y, 0});
	}

	void Game::e_agentdeath(const event::eAgentDeath& event)
	{
		object::GameObject* gameobject = event.victim;
		RemoveGameObject(gameobject);
	}

	void Game::init_entities()
	{
		// player
		object::GameObject* playerobj = object::GameObject::Create(
			{ 200.0f,  200.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 32.0f,   32.0f,   32.0f }
		);
		m_player = new object::Player(playerobj, "player");
		AddGameObject(m_player);

		// camera
		object::GameObject* cameraobj = object::GameObject::Create(
			{ 0.0f,   0.0f,   0.0f },
			{ 0.0f,   0.0f,   0.0f },
			{ 300.0f, 300.0f, 300.0f }
		);
		m_camera = new object::Camera(cameraobj);
		m_camera->SetSubject(m_player);
	}

	void Game::init_textelements()
	{
		object::GameObject* consoletxtobj = object::GameObject::Create({ 4.0f,    4.0f,    0.0f }, 0, 0);
		m_consoletxt = new object::TextObject(consoletxtobj, "HenryBlue-Regular", "", { 0, 255, 0 });
		AddGameObject(m_consoletxt);

		object::GameObject* coordtextobj = object::GameObject::Create(0, 0, 0);
		m_coords = new object::TextObject(coordtextobj, "HenryBlue-Regular", "", { 0, 0, 0 });
		AddGameObject(m_coords);
	}

	void Game::do_textelements()
	{
		// console
		bool active = console::ACTIVE;
		m_consoletxt->GetTexture()->Active(active);
		if (active)
		{
			if (console::SPECIAL) { m_consoletxt->SetText("done!"); }
			else { m_consoletxt->SetText(console::m_inputstr); }
		}
		else { m_consoletxt->SetText(""); }

		// coords
		if (m_camera->GetSubject() != nullptr)
		{
			// get current subject coords
			object::Transform* subject_transform = &m_camera->GetSubject()->GetTransform();
			Vector2D pos = subject_transform->Get2DPosition();
			std::string coords = std::string(std::to_string((int)roundf(pos.x)) + " " + std::to_string((int)roundf(pos.y)));

			// offset pos & draw coords
			Vector2D offsetpos = pos - m_camera->GetOffsetpos();
			m_coords->GetTexture()->Pos(offsetpos + Vector2D{0, -20});
			m_coords->SetText(coords);
		}
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
			m_selected_obj = get_clickedobject(x, y);
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
			float _x = x + m_camera->GetOffsetpos().x;
			float _y = y + m_camera->GetOffsetpos().y;
			object::GameObject* miscagent = object::GameObject::Create(
				{ _x,	   _y,      0.0f },
				{ 0.0f,    0.0f,    0.0f },
				{ 64.0f,   64.0f,   64.0f }
			);
			int sides = maths::GetRandomInt(2, 6);
			AddGameObject(new object::Agent(miscagent, sides));
		}
		break;
		case 2: // mm
		{
		}
		break;
		case 4: // m2
		{
			object::GameObject* obj = get_clickedobject(x, y);
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

	object::GameObject* Game::get_clickedobject(int x, int y)
	{
		for (object::GameObject* object : m_gameobjects)
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
		srand((int)time(NULL)); // move me

		init_entities();

		// debug
		object::GameObject* miscagent = object::GameObject::Create(
			{ 100.0f,  400.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 32.0f,   32.0f,   32.0f }
		);
		AddGameObject(new object::Agent(miscagent, 8));

		object::GameObject* food = object::GameObject::Create(
			{ 600.0f,  400.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 64.0f,   64.0f,   64.0f }
		);
		AddGameObject(new object::Food(food, "food"));

		object::GameObject* triman = object::GameObject::Create(
			{ 0.0f,     0.0f,    0.0f },
			{ 0.0f,     0.0f,    0.0f },
			{ 64.0f,    64.0f,   64.0f }
		);
		object::Agent* triagent = new object::Agent(triman, 4);
		AddGameObject(triagent);
		triagent->SetTargetpos({ 500, 500 });

		init_textelements();
	}

	// entities -> camera
	void Game::Tick()
	{
		// tick/collision objects
		for (object::GameObject* gameobject : m_gameobjects)
		{
			m_collision->CheckCollisionObj(gameobject);
			m_collision->DoCollision();
			gameobject->Tick();
		}

		// camera
		m_camera->Tick();

		// console
		do_textelements();

		// update what camera sees
		for (object::GameObject* gameobject : m_gameobjects)
		{
			if (gameobject == m_consoletxt || gameobject == m_coords) { continue; } // hack for console & coord text
			m_camera->SetTexturePos(gameobject);
		}

		for (int i = 0; i < m_toremove.size(); i++)
		{
			delete m_toremove[i];
		}
		m_toremove.clear();
	}
}