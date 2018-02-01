#ifndef ENGINE_WINDOW_HPP
#define ENGINE_WINDOW_HPP

#include <engine/entity.hpp>
#include <map>
#include <memory>

namespace engine
{
	class window
	{
	public:
		window()
		{
			m_window.create(sf::VideoMode::getDesktopMode(), "Game Window");
			m_window.setVerticalSyncEnabled(true);
		}

		void setTitle(const sf::String& title)
		{
			m_window.setTitle(title);
		}

		void render()
		{
			sf::Event event;

			while (m_window.pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
						m_window.close();
						break;

					case sf::Event::KeyPressed:
						break;

					case sf::Event::KeyReleased:
						break;

					case sf::Event::Resized:
						m_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
						break;
				}
			}

			m_window.clear();

			draw();

			m_window.display();
		}

		bool isOpen()
		{
			return m_window.isOpen();
		}

		void draw()
		{
			for (auto&& i : m_entity_map)
				i.second->render(m_window);
		}

		void update()
		{
			for (auto&& i : m_entity_map)
				i.second->update();
		}

		void add_entity(sf::String id, entity* e)
		{
			m_entity_map[id] = std::unique_ptr<entity>(e);
		}

		void del_entity(sf::String id)
		{
			m_entity_map.erase(id);
		}

	private:
		sf::RenderWindow m_window;
		std::map<sf::String, std::unique_ptr<entity>> m_entity_map;
	};
}

#endif