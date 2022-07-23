#include "engine.h"

namespace base
{
    static int          m_fps_cap;
    static int          m_tick_rate;
    static bool         m_is_paused;
    static bool         m_shutdown_requested;

    bool Init()
    {
        std::cout << "initializing the game engine\n";

        // set default values
        m_fps_cap = 150;
        m_tick_rate = 64;
        m_is_paused = false;
        m_shutdown_requested = false;

        // create renderer
        renderer::Renderer::Create();

        // create game
        game::Game::Create();

        // create updater
        updater::Updater::Create();

        return true;
    }

    void Run()
    {
        SDL_Event m_events;

        // assign and start the renderer
        static renderer::Renderer* renderer = renderer::Renderer::Get();
        if (!renderer->Start("POGengine", 640, 480)) { m_shutdown_requested = true; }  

        // assign and start the game
        static game::Game* game = game::Game::Get();
        game->Start();

        // assign the updater static object
        static updater::Updater* updater = updater::Updater::Get();

        // start the timers
        timer::Timer* m_tick_timer = new timer::Timer();
        timer::Timer* m_fps_timer = new timer::Timer(); 

        while (!m_shutdown_requested)
        {
            // tick the timers
            m_tick_timer->Update();
            m_fps_timer->Update();

            // if want to exit
            while (SDL_PollEvent(&m_events) != 0)
            {
                switch (m_events.type)
                {
                    case SDL_QUIT:
                        m_shutdown_requested = true;
                        break;
                }
            }

            if (m_shutdown_requested)
            {
                renderer->Clean();
                continue;
            }

            // game tick
            if (m_tick_timer->DeltaTime() >= 1.0f / m_tick_rate)
            {
                // tick the updater [handles inputs] then the game (& its objects)
                updater->Tick();
                game->Tick();
            
                m_tick_timer->Reset();
            }

            // render tick
            if (m_fps_timer->DeltaTime() >= 1.0f / m_fps_cap)
            {
                // render the frame
                renderer->Render();
                m_fps_timer->Reset();
            }

        }
    }

    void Stop()
    {
        renderer::Renderer::Destroy();
    }
}