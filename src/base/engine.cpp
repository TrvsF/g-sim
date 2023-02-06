#include "engine.h"

namespace base
{
    static const int    m_tick_rate             = 64;
    static int          m_fps_cap               = 150;
    static bool         m_shutdown_requested    = false;

    bool Init()
    {       
        // TODO : run startup checks ^^(maybe with the vars above)^^
        return true;
    }

    void Run()
    {
        SDL_Event m_events;

        // start the renderer
        if (!renderer::Renderer::SharedInstace().Start("tri-engine", 640, 480)) 
        { m_shutdown_requested = true; }

        // start the game
        game::Game::SharedInstace().Start();

        // start the timers
        timer::Timer* m_tick_timer = new timer::Timer();
        timer::Timer* m_fps_timer  = new timer::Timer();

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
                renderer::Renderer::SharedInstace().Clean();
                continue;
            }

            // game tick
            if (m_tick_timer->DeltaTime() >= 1.0f / m_tick_rate)
            {
                // tick the updater [handles inputs] then the game (& its objects)
                updater::Updater::SharedInstance().Tick();
                game::Game::SharedInstace().Tick();
                m_tick_timer->Reset();
            }

            // render tick
            if (m_fps_timer->DeltaTime() >= 1.0f / m_fps_cap)
            {
                // render the frame
                renderer::Renderer::SharedInstace().Render();
                m_fps_timer->Reset();
            }
        }
    }

    void Stop()
    {
        // TODO : clean objects
    }
}