#include <engine/loop.hpp>

class ball: public engine::entity
{
public:
	ball()
	{
		shape.setRadius(30);
	}

	void update()
	{
		y += v / 60.0;
		if (y <= 0)
		{
			y = 0;
			v = -0.7 * v;
		}
		v += a / 60.0;
	}

	void render(sf::RenderTarget& target)
	{
		auto size = target.getSize();

		shape.setPosition(size.x / 2 - 30, 60 + (1 - y) * (size.y - 120));
		target.draw(shape);
	}

private:
	float v = 0;
	float y = 1;
	float a = -0.2;

	sf::CircleShape shape;
};

int main()
{
	engine::loop loop("Ball bounce", 60.0);

	ball b;
	loop.get_window().add_entity("entity:ball", &b);

	loop.start();

	return 0;
}