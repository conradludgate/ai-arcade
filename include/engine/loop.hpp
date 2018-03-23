#ifndef ENGINE_LOOP_HPP
#define ENGINE_LOOP_HPP

#include <engine/game.hpp>
#include <chrono>
#include <ctime>
#include <ratio>

namespace engine
{
	class loop
	{

	public:
		loop(const sf::String &title, int fps = 60.0)
		{
			delta = 1000000.0f / fps;

			m_window.create(sf::VideoMode::getDesktopMode(), title);
			m_window.setVerticalSyncEnabled(true);
		}

		void start();
		void render();
		void poll_events(uint64_t);

		void setGame(game* g)
		{
			m_game = g;
			m_game->m_window = &m_window;
		}
		
	private:
		double delta;

		sf::RenderWindow m_window;

		game* m_game = nullptr;
	};
}

#endif