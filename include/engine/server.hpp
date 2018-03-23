#ifndef ENGINE_SERVER_HPP
#define ENGINE_SERVER_HPP

#include <SFML/Network.hpp>
#include <engine/entity-manager.hpp>
#include <thread>
#include <memory>
#include <vector>
#include <ctime>
#include <functional>

#ifdef DEBUG
#define DEBUG_LOG(...) printf (__VA_ARGS__)
#else
#define DEBUG_LOG(...)
#endif

namespace engine
{
	enum message
	{
		CONNECT,
		POLL,
		EVENT,
		SYNC
	};

	class server
	{
	public:
		struct client
		{
			sf::IpAddress ip;
			uint16_t port;

			std::map<sf::String, time_t> sync;
		};

		bool bind(uint16_t port)
		{
			return m_socket.bind(port) == sf::Socket::Done;
		}

		// static std::unique_ptr<std::thread> serve(uint16_t port)
		// {
		// 	return std::make_unique<std::thread>(&server::m_serve, port);
		// }

		std::thread listen();

		void handle(sf::Packet&, sf::IpAddress, uint16_t);
		void sync(engine::server::client&, sf::Packet&);

		void attach(sf::String key, entity_manager& em)
		{
			m_managers[key] = em;
		}

		void detach(sf::String key)
		{
			m_managers.erase(key);
		}

		std::function<bool (sf::Packet&)> authenticate = 
			[](sf::Packet& p) {return true;};

		std::function<void (sf::Event)> event_handler = 
			[](sf::Event e) {};

		std::function<void (engine::server::client&, sf::Packet&)> poll_handler = 
			[](engine::server::client& c, sf::Packet& p) {};

	private:
		//static void m_serve(uint16_t port);
		//void handle_connect(sf::Packet, sf::IpAddress, uint16_t);

		std::map<uint64_t, client> m_clients;
		sf::UdpSocket m_socket;

		std::map<sf::String, entity_manager&> m_managers;
	};
}

#endif