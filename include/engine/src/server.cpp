#include <engine/server.hpp>
#include <random>
#include <string>

// void engine::server::m_serve(uint16_t port)
// {
// 	server serv;
// 	serv.bind(port);
// 	serv.listen();
// }

std::thread engine::server::listen()
{
	return std::thread([this]() -> void
	{
		while (true)
		{
			sf::Packet packet;
			sf::IpAddress sender;
			unsigned short port;

			if (m_socket.receive(packet, sender, port))
			{
				// error occured, do... something? maybe just ignore.
			}

			handle(packet, sender, port);
		}
	});
}

bool check_user(engine::server::client& c, sf::IpAddress ip, uint16_t port)
{
	return (c.ip == ip) && (c.port = port);
}

template<typename T>
T get(sf::Packet& p)
{
	T t;
	p >> t;
	return t;
}

// sf::String get_string(sf::Packet& p)
// {
// 	sf::Uint8 count = get<sf::Uint8>(p);
// 	char buffer [count];
// 	p >> buffer;
// 	return buffer
// }

// void write_string(sf::Packet& p, sf::String d)
// {
// 	p << (sf::Uint8)std::char_traits<char>::length(d);
// 	p << d;
// }

void engine::server::handle(sf::Packet& packet, sf::IpAddress ip, uint16_t port)
{
	int msg = get<sf::Uint8>(packet);

	//uint64_t key = get<sf::Uint64>(packet);
	int key = get<sf::Int32>(packet);

	DEBUG_LOG("Message from %s:%d -> ", ip, port);

	switch (msg)
	{
		case message::CONNECT:
			DEBUG_LOG("CONNECT");

			if (authenticate(packet))
			{
				// std::random_device rd;
				// std::mt19937_64 gen(rd());
				// std::uniform_int_distribution<uint64_t> dis();

				// key = dis(gen);
				key = rand();
				auto it = m_clients.find(key);

				while (it != m_clients.end())
				{
					//key = dis(gen);
					key = rand();
					it = m_clients.find(key);
				}
				
				m_clients[key] = {ip, port};
			}
			
			break;

		case message::POLL:
			DEBUG_LOG("POLL");

			auto c = m_clients[key];
			if (check_user(c, ip, port))
				poll_handler(c, packet);

			break;

		case message::EVENT:
			DEBUG_LOG("EVENT");

			

			if (check_user(m_clients[key], ip, port))
				event_handler(packet);

			break;
		
		case message::SYNC:
			DEBUG_LOG("SYNC");

			auto c = m_clients[key];
			if (check_user(c, ip, port))
			{
				sync(c, packet);
			}

			break;
				
		// default:
		// 	DEBUG_LOG("%s\n", packet);
		// 	break;
	}
}

void engine::server::sync(engine::server::client& c, sf::Packet& p)
{
	time_t t;
	time(&t);

	sf::Packet sync_p;

	while(!p.endOfPacket())
	{
		auto man_name = get<sf::String>(p);

		if (c.sync[man_name] < t)
		{
			auto man = m_managers.find(man_name);
			if (man != m_managers.end())
			{
				sync_p << man_name;
				sync_p << (*man).second;
			}
		}
	}
}