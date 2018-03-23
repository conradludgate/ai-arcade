#ifndef ENGINE_CLIENT_HPP
#define ENGINE_CLIENT_HPP

namespace engine
{
	class client
	{
		void connect(sf::IpAddress, uint16_t);

		void poll();

		void event();
		
		void sync();
	};
}

#endif