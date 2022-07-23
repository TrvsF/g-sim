#include "../timer.h"

namespace timer
{
	timer::Timer::Timer()
	{
		Reset();
	}

	Timer::~Timer()
	{
	}

	void timer::Timer::Reset()
	{
		m_elapsed_ticks = 0;
		m_delta_time = 0;
		m_start_ticks = SDL_GetTicks();
	}

	void timer::Timer::Update()
	{
		m_elapsed_ticks = SDL_GetTicks() - m_start_ticks;
		m_delta_time = m_elapsed_ticks * 0.001f;
	}

	float timer::Timer::DeltaTime()
	{
		return m_delta_time;
	}

}

