#ifndef TIMER_H_
#define TIMER_H_

#include <SDL.h>

namespace timer
{
	class Timer
	{
	private:
		int m_start_ticks;
		int m_elapsed_ticks;
		float m_delta_time;

	public:
		Timer();
		virtual ~Timer();

		void Reset();
		void Update();
		float DeltaTime();
	};
}

#endif // !TIMER_H_
