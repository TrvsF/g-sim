#include "../engine.h"

namespace engine
{
    static int fps_cap_;
    static int tick_rate_;
    static bool is_paused_;
    static bool shutdown_requested_;

    bool Init()
    {
        std::cout << "initializing the game engine\n";

        // set default values
        fps_cap_ = 150;
        tick_rate_ = 20;
        is_paused_ = false;
        shutdown_requested_ = false;

        std::cout << "starting the renderer\n";

        // create renderer
        renderer::Renderer::Create();

        // create updater
        updater::Updater::Create();

        return true;
    }

    void Run()
    {
        SDL_Event m_events;
        
        static updater::Updater* updater = updater::Updater::Get();
        static renderer::Renderer* renderer = renderer::Renderer::Get();
        renderer->Start("POGengine", 640, 480);

        timer::Timer* m_tick_timer = new timer::Timer();
        timer::Timer* m_fps_timer = new timer::Timer(); 

        while (!shutdown_requested_)
        {
            m_tick_timer->Update();
            m_fps_timer->Update();

            // if want to exit
            while (SDL_PollEvent(&m_events) != 0)
            {
                switch (m_events.type)
                {
                    case SDL_QUIT:
                        shutdown_requested_ = true;
                        break;
                }
            }

            if (shutdown_requested_)
            {
                renderer->Clean();
                continue;
            }

            // a game tick
            if (m_tick_timer->DeltaTime() >= 1.0f / tick_rate_)
            {
                m_tick_timer->Reset();
                updater->Tick();
            }

            // a render tick
            if (m_fps_timer->DeltaTime() >= 1.0f / fps_cap_)
            {
                m_fps_timer->Reset();
                renderer->Render();
            }

        }
    }

    void Stop()
    {
        renderer::Renderer::Destroy();
    }
}