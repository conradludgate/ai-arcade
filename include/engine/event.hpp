#ifndef ENGINE_EVENT_HPP
#define ENGINE_EVENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace engine
{
	class Event
	{
	public:
		Event(uint64_t tick)
		{
			tick = tick;
			type = None;
		}

		uint64_t tick;

		struct ServerMessageEvent
		{
			const char* message;
		};
		
		enum EventType
		{
			KeyDown,
			KeyUp,

			MouseDown,
			MouseUp,
			MouseMove,
			MouseScroll,

			ServerMessage,

			Close,
			Resize,

			None
		};

		EventType type;

		union
		{
			sf::Event::KeyEvent key;
			sf::Event::MouseButtonEvent mouseButton;
			sf::Event::MouseMoveEvent mouseMove;
			sf::Event::MouseWheelScrollEvent mouseScroll;
			ServerMessageEvent message;
			sf::Event::SizeEvent size;
		};

		friend sf::Packet& operator>>(sf::Packet& p, const Event& e)
		{
			e.type << p;
			switch (e.type)
			{
				case KeyDown, KeyUp:
					sf::Uint8 keycode;
					p >> keycode;

					e.key.code = keycode;
					p >> e.alt;
					p >> e.control;
					p >> e.shift;
					p >> e.system;
					break;

				case MouseDown, MouseUp:
					sf::Uint8 button;
					p >> button;

					e.mouseButton.button = button;

					sf::Int32 x, y;
					p >> x >> y;

					e.mouseButton.x = x;
					e.mouseButton.y = y;
					break;

				case MouseMove:
					sf::Int32 x, y;
					p >> x >> y;

					e.mouseMove.x = x;
					e.mouseMove.y = y;
					break;

				case MouseScroll:
					sf::Uint8 wheel;
					p >> wheel;

					e.mouseScroll.wheel = wheel;

					p >> e.mouseScroll.delta;

					sf::Int32 x, y;
					p >> x >> y;

					e.mouseScroll.x = x;
					e.mouseScroll.y = y;
					break;

				case ServerMessage:
					p >> e.message.message;

				case Resize:
					sf::Uint32 width, height;
					p >> width >> height;

					e.size.width = width;
					e.size.height = height;
					break;
			}
		}
	};
}
#endif