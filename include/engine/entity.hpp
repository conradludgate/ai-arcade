#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP value

#include <SFML/Graphics.hpp>

namespace engine
{
	class entity
	{
	public:
		virtual void update() = 0;
		virtual void render(sf::RenderTarget& target) = 0;
	};
}

#endif