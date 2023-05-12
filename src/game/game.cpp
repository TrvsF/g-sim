#include "game.h"

namespace game
{
	Game::Game()
	{
		// collision
		m_collision = new Collision(128);

		// vars
		m_player	   = nullptr;
		m_camera       = nullptr;
		m_consoletxt   = nullptr;
		m_coords       = nullptr;
		m_debugname	   = nullptr;
		m_debugfollow  = nullptr;

		// events
		m_listener.listen<event::ePosChange> (std::bind(
			&Game::e_poschange, this, std::placeholders::_1));
		m_listener.listen<event::eObjectDeath>(std::bind(
			&Game::e_objectdeath, this, std::placeholders::_1));
		m_listener.listen<event::eScaleChange>(std::bind(
			&Game::e_scalechange, this, std::placeholders::_1));
		m_listener.listen<event::eAgentBorn>(std::bind(
			&Game::e_agentbirth, this, std::placeholders::_1));
	}

	void Game::e_poschange(const event::ePosChange& event)
	{
		m_player->SetPosition({event.pos.x, event.pos.y, 0});
	}

	void Game::e_scalechange(const event::eScaleChange& event)
	{
		renderer::Renderer::SharedInstace().Scale(event.scale);
	}

	void Game::e_objectdeath(const event::eObjectDeath& event)
	{
		object::GameObject* gameobject = event.victim;
		RemoveGameObject(gameobject);
	}

	void Game::e_agentbirth(const event::eAgentBorn& event)
	{
		std::string genus;
		god::generate_child_genome(event.g1, event.g2, genus);

		m_tobeborn.push_back({ event.pos.x, event.pos.y, genus, event.lastname });

		// spawn_agent(event.pos.x, event.pos.y, genus, event.lastname);
	}

	void Game::init_entities()
	{
		// player
		object::GameObject* playerobj = object::GameObject::Create(
			{ 200.0f,  200.0f,  0.0f },
			{ 0.0f,    0.0f,    0.0f },
			{ 16.0f,   16.0f,   32.0f }
		);
		m_player = new object::Player(playerobj, "player");
		AddGameObject(m_player);

		// camera
		object::GameObject* cameraobj = object::GameObject::Create(
			{ 0.0f,   0.0f,   0.0f },
			{ 0.0f,   0.0f,   0.0f },
			{ 720.0f, 720.0f, 300.0f }
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

		object::GameObject* debugtextobj = object::GameObject::Create(0, 0, 0);
		m_debugname = new object::TextObject(debugtextobj, "HenryBlue-Regular", "", { 0, 0, 0 });
		AddGameObject(m_debugname);
	}

	void Game::generate_map()
	{
		for (int i = -5; i < 5; i+=2)
		{
			for (int j = -5; j < 5; j+=2)
			{
				int x = maths::GetRandomInt((i * 250) - 250, (i * 250) + 250);
				int y = maths::GetRandomInt((j * 250) - 250, (j * 250) + 250);
				spawn_food(x, y, 15000);
			}
		}
	}

	void Game::spawn_agent(int x, int y, std::string genus, std::string lastname)
	{
		object::GameObject* gameobject = object::GameObject::Create(
			{ (float)x, (float)y, 0.0f },
			{ 0.0f,     0.0f,     0.0f },
			{ 64.0f,    64.0f,    64.0f }
		);
		object::Agent* agent = new object::Agent(gameobject, { {0, 0}, {50, 0}, {0, 50} });

		if (genus == "")
		{
			god::GenerateGenus(genus);
		}
		// if does not build successfully
		if (!god::BuildAgent(agent, genus))
		{
			agent->GetGeometry()->Active(false); // TODO : bug
			RemoveGameObject(agent);
			return;
		}

		// random first & last name
		agent->SetName("", true);
		agent->SetName(lastname, false);

		console::bus->postpone(event::eObjectSpawn { agent });
		console::bus->process();

		AddGameObject(agent);
	}

	void Game::spawn_food(int x, int y, int size)
	{
		object::GameObject* food = object::GameObject::Create(
			{ (float)x, (float)y, 0.0f },
			{ 0.0f,     0.0f,     0.0f },
			{ 64.0f,    64.0f,    64.0f }
		);
		AddGameObject(new object::Food(food, maths::GetRandomInt(0, 3), size));
	}

	void Game::zoom(float zoom, Vector2D mousepos)
	{
		// set global zoom
		float scale = renderer::Renderer::SharedInstace().Scale();
		float newscale = scale + (zoom);
		if (newscale < 0.5f) { return; }
		// 'globally' set the new scale
		renderer::Renderer::SharedInstace().Scale(newscale);
		renderer::Renderer::SharedInstace().ScalePos(mousepos);
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
		if (m_camera != nullptr)
		{
			// get current subject coords
			Vector2D pos = m_camera->GetTransform().Get2DPosition();
			std::string coords = std::string(std::to_string((int)roundf(pos.x)) + " " + std::to_string((int)roundf(pos.y)));

			// offset pos & draw coords
			m_coords->GetTexture()->Pos(Vector2D{20, 240});
			m_coords->SetText(coords);
		}

		// debug agent
		if (m_debugfollow != nullptr)
		{
			object::Transform* subject_transform = &m_debugfollow->GetTransform();
			Vector2D pos = subject_transform->Get2DPosition();

			m_debugname->GetTexture()->Pos(Vector2D{20, 300});
			m_debugname->SetText(m_debugfollow->GetName());
		}
	}

	void Game::MouseRelease(int mousebutton)
	{
		switch (mousebutton)
		{
		case 1:
			break;
		}
	}

	void Game::MouseDown(int mousebutton, int x, int y)
	{
		switch (mousebutton)
		{
		case 8:
			zoom(-0.02f, {(float)x, (float)y });
			break;
		case 16:
			zoom(0.02f, { (float)x, (float)y });
			break;
		}
	}

	void Game::MouseClick(int mousebutton, int x, int y)
	{
		switch (mousebutton)	
		{
		case 1: // m1
		{
			float _x = x + m_camera->GetOffsetpos().x;
			float _y = y + m_camera->GetOffsetpos().y;

			bool multicolour = R && G && B;
			std::string genus;
			god::GenerateGenus(genus);
			// RED
			god::overwrite_gene(genus, 99, R ? '1' : '0');
			// GREEN
			god::overwrite_gene(genus, 126, G ? '1' : '0');
			// BLUE
			god::overwrite_gene(genus, 153, B ? '1' : '0');

			spawn_agent(_x, _y, multicolour ? "" : genus, "");
		}
		break;
		case 2: // mm
		{
			const auto& clicked = get_clickedobject(x, y);
			if (clicked == NULL)
			{
				m_debugname->SetText("");
				m_debugfollow = nullptr; 
				return;
			}
			// if clicked agent
			if (clicked->GetEntityType() == object::GameEntityType::Agent)
			{
				const auto& agent = static_cast<object::Agent*>(clicked);
				m_debugfollow = agent;
			}
		}
		break;
		case 4: // m2
		{
			float _x = x + m_camera->GetOffsetpos().x;
			float _y = y + m_camera->GetOffsetpos().y;
			spawn_food(_x, _y, R ? 500000 : 25000);
		}
		break;
		}
	}

	void Game::ScrollDown(int mousebutton, int x, int y)
	{

	}

	void Game::ScrollUp(int mousebutton, int x, int y)
	{

	}

	void Game::MoveCamera(Vector2D movevec)
	{
		m_camera->Offset(movevec);
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
			{ return object; }
		}
		return nullptr;
	}

	void Game::Start()
	{
		srand((int)time(NULL)); // move me

		init_entities();
		init_textelements();
		// generate_map();
	}

	// entities -> camera
	void Game::Tick()
	{
		// remove entities that died last tick
		std::for_each(m_toremove.begin(), m_toremove.end(), maths::delete_pointer_element<object::GameObject*>());
		m_toremove.clear();

		// main camera tick
		m_camera->Tick();

		// update what camera sees
		for (object::GameObject* gameobject : m_gameobjects)
		{
			if (gameobject == m_consoletxt || gameobject == m_coords) { continue; } // hack for console & coord text
			m_camera->SetTexturePos(gameobject);
		}

		// tick & collision objects
		for (object::GameObject* gameobject : m_gameobjects)
		{
			m_collision->CheckCollisionObj(gameobject);
			m_collision->DoCollision();
			gameobject->Tick();
		}

		// TODO : bad hack!
		for (const auto& obj : m_tobeborn)
		{
			spawn_agent(obj.x, obj.y, obj.genus, obj.lastname);
		}
		m_tobeborn.clear();

		// text on screen
		do_textelements();
	}
}