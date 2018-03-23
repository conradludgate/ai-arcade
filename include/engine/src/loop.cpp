#include <engine/loop.hpp>

void engine::loop::start()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	uint64_t accumulator = 0;

	uint64_t game_tick = 0;

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
			m_game->update(game_tick++);

			accumulator -= delta;
		}

		render();
	}
}

void engine::loop::poll_events(uint64_t game_tick)
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		Event e(game_tick);
		switch (event.type)
		{
			case sf::Event::Closed:
				//m_window.close();
				//game type can close the window once it's finished
				e.type = Event::Close;
				break;

			case sf::Event::Resized:
				m_window.setView(sf::View(
					sf::FloatRect(0, 0, event.size.width, event.size.height)));
				e.type = Event::Resize;
				e.size = event.size;
				break;

			case sf::Event::KeyPressed:
				e.type = Event::KeyDown;
				e.key = event.key;
				break;

			case sf::Event::KeyReleased:
				e.type = Event::KeyUp;
				e.key = event.key;
				break;

			case sf::Event::MouseButtonPressed:
				e.type = Event::MouseDown;
				e.mouseButton = event.mouseButton;
				break;

			case sf::Event::MouseButtonReleased:
				e.type = Event::MouseUp;
				e.mouseButton = event.mouseButton;
				break;

			case sf::Event::MouseMoved:
				e.type = Event::MouseMove;
				e.mouseMove = event.mouseMove;
				break;

			case sf::Event::MouseWheelScrolled:
				e.type = Event::MouseScroll;
				e.mouseScroll = event.mouseWheelScroll;
				break;
		}

		if (e.type != Event::None)
		{
			m_game->push_event(e);
		}
	}
}

void engine::loop::render()
{
	m_window.clear();

	m_game->render();

	m_window.display();
}