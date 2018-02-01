#ifndef ENGINE_LOOP_HPP
#define ENGINE_LOOP_HPP

#include <engine/window.hpp>
#include <chrono>
#include <ctime>
#include <ratio>

//#include <engine/server.hpp>

namespace engine
{
	class loop
	{

	public:
		loop(const sf::String &title, int fps = 60.0)
		{
			delta = 1000000.0f / fps;
			m_window.setTitle(title);
		}

		void start()
		{
			auto current_time = std::chrono::high_resolution_clock::now();
			uint64_t accumulator = 0;

			while (m_window.isOpen())
			{
				auto new_time = std::chrono::high_resolution_clock::now();

				auto frame_delta = std::chrono::duration_cast
					<std::chrono::microseconds>(new_time - current_time)
					.count();

				if (frame_delta > 250000)
					frame_delta = 250000;

				current_time = new_time;

				accumulator += frame_delta;

				while (accumulator >= delta)
				{
					m_window.update();

					accumulator -= delta;
				}

				const double alpha = accumulator / delta;

				m_window.render();
			}
		}

		window& get_window()
		{
			return m_window;
		}
		
	private:
		double delta;

		window m_window;
	};
}

#endif