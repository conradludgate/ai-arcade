#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP

#include <SFML/Network.hpp>
#include <engine/event.hpp>

#ifdef DEBUG
#define DEBUG_LOG(...) printf (__VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif

namespace engine
{
	class game;
	class entity_manager;

	class entity
	{
	public:
		virtual void update(const std::vector<Event>& events) = 0;
		virtual void render() = 0;

		virtual int type()
		{
			return -1;
		}

		virtual sf::String type_name()
		{
			return "";
		}

		void set_id(uint64_t id) { entity_id = id; }
		uint64_t id() { return entity_id; }

	private:
		uint64_t entity_id;
	};

	sf::Packet& operator<<(sf::Packet& p, const entity* e);
	sf::Packet& operator>>(sf::Packet& p, entity* e);
}

#endif