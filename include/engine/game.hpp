#ifndef ENGINE_GAME_HPP
#define ENGINE_GAME_HPP

#include <engine/entity.hpp>

namespace engine
{
	class loop;

	class game
	{
		friend class loop;

	public:
		virtual void update(uint64_t) = 0;
		virtual void render() = 0;

		virtual void draw(const sf::Drawable& d)
		{
			m_window->draw(d);
		}

		virtual void push_event(Event e)
		{
			events.push_back(e);
		}

		virtual entity* create_entity(int type);

		// bool hostServer(uint16_t port)
		// {
		// 	if (!m_server.bind(port))
		// 	{
		// 		return false;
		// 	}

		// 	DEBUG_LOG("Bound to port %d", port);

		// 	m_thread = std::thread([this]() {this->m_server.listen();});
		// }

		// bool connectServer(sf::IpAddress ip)
		// {
		// 	return false;
		// }

	protected:
		sf::RenderTarget* m_window = nullptr;

		// EVENTS:
		// Events are stored in a vector in order.
		// Every physics update, the vector is copied, with the original being cleared
		// Each entity in the world is passed an iterator across the events, to deal with how they like
		// Works kinda like events and polling at the same time.
		// Removes need for awkward entity destroy methods

		// Immutable Events, because entities shouldn't need to change them
		// they can always just push their own messages...
		std::vector<Event> events;
	};
}

#endif