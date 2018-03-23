#include <engine/entity.hpp>

namespace engine
{
	sf::Packet& operator<<(sf::Packet& p, const entity* e)
	{
		return p;
	}

	sf::Packet& operator>>(sf::Packet& p, entity* e)
	{
		return p;
	}
}