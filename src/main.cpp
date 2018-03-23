#include <engine/loop.hpp>
#include <cmath>

// Ball bouce test
class ball: public engine::entity
{
private:
	sf::Vector2f m_position;
	sf::CircleShape m_shape;

	float speed = 0.75;
	sf::Vector2f d;

public:
	// Create Ball
	ball()
	{
		m_shape.setRadius(50);
		m_shape.setOrigin(25, 25);
	}

	// Physics
	void update(const std::vector<engine::Event>& events)
	{
		for (auto&& event: events)
		{
			if (event.type == engine::Event::KeyDown)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::W:
					case sf::Keyboard::Up:
						if (d.y <= 0)
							d.y += 1;
						break;
					case sf::Keyboard::S:
					case sf::Keyboard::Down:
						if (d.y >= 0)
							d.y -= 1;
						break;
					case sf::Keyboard::D:
					case sf::Keyboard::Right:
						if (d.x <= 0)
							d.x += 1;
						break;
					case sf::Keyboard::A:
					case sf::Keyboard::Left:
						if (d.x >= 0)
							d.x -= 1;
						break;
				}
			}
			if (event.type == engine::Event::KeyUp)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::W:
					case sf::Keyboard::Up:
						if (d.y >= 0)
							d.y -= 1;
						break;
					case sf::Keyboard::S:
					case sf::Keyboard::Down:
						if (d.y <= 0)
							d.y += 1;
						break;
					case sf::Keyboard::D:
					case sf::Keyboard::Right:
						if (d.x >= 0)
							d.x -= 1;
						break;
					case sf::Keyboard::A:
					case sf::Keyboard::Left:
						if (d.x <= 0)
							d.x += 1;
						break;
				}
			}
		}

		float len = sqrt(d.x * d.x + d.y * d.y);
		if (len > 0)
			m_position += (d / len) * speed / 60.0f;
	}

	// Graphics
	void render()
	{
		m_shape.setPosition(m_game->getWinPos(m_position));
		m_game->draw(m_shape);
	}
};

int main()
{
	// Setup game loop
	engine::loop loop("Ball bounce", 60.0);

	// Add ball entity to window
	ball b;
	loop.get_world().add_entity("entity:ball", &b);

	// Start game
	loop.start();

	return 0;
}