#ifndef ENGINE_ENTITY_MANAGER_HPP
#define ENGINE_ENTITY_MANAGER_HPP

#include <engine/game.hpp>
#include <engine/entity.hpp>
#include <memory>
#include <map>
#include <vector>

namespace engine
{
	class entity_manager
	{
	public:
		entity_manager(game* g, sf::String name)
		{
			m_game = g;
			m_name = name;
		}

		entity* create_entity(int type)
		{
			entity* e = m_game->create_entity(type);

			DEBUG_LOG("Attaching entity %s %d to %s\n",
						e->type_name(), m_id, m_name);

			m_entities.push_back(e);
			e->set_id(m_id++);

			return e;
		}

		// Returns false if entity doesn't exist.
		bool pop_entity(uint64_t id, entity* e)
		{
			for (auto i = m_entities.begin(); i != m_entities.end(); i++)
			{
				if ((*i)->id() == id)
				{
					DEBUG_LOG("Removing entity %s %d from %s\n",
						(*i)->type_name(), id, m_name);

					e = *i;
					m_entities.erase(i);
					return true;
				}
			}

			return false;
		}

		void render()
		{
			for (auto& i : m_entities)
			{
				i->render();
			}
		}

		void update(const std::vector<Event> events)
		{
			for (auto& i : m_entities)
			{
				i->update(events);
			}
		}

		friend sf::Packet& operator<<(sf::Packet& p, const entity_manager& em)
		{
			int count = em.m_entities.size();
			p << count;

			DEBUG_LOG("%s syncing %d entities with clients", em.m_name, count);

			for (auto& i : em.m_entities)
			{
				p << (sf::Uint64)i->id();
				p << (sf::Int32)i->type();
				p << i;
			}
		}

		friend sf::Packet& operator>>(sf::Packet& p, entity_manager& em)
		{
			int count;
			p >> count;

			if (count == 0)
			{
				em.m_entities.clear();
				return p;
			}

			DEBUG_LOG("%s syncing %d entities with server", em.m_name, count);

			sf::Uint64 id;
			sf::Int32 type;
			p >> id >> type;

			int i = 1;
			for (auto e = em.m_entities.begin(); e != em.m_entities.end(); e++)
			{
				if ((*e)->id() > id)
				{
					// The server knows of an entity
					// that the client doesn't know about
					e = em.m_entities.insert(e, em.m_game->create_entity(type));
					(*e)->set_id(id);
				}

				if ((*e)->id() == id)
				{
					if ((*e)->type() != type)
					{
						// Entity mismatch - Should we recreate this entity?
					}

					// Update 
					p >> (*e);
					
					if (i++ >= count) break;
					
					p >> id >> type;
				}
				else 
				{
					// Kill entity, Server no longer knows this entity
					em.m_entities.erase(e);
				}
			}

			em.m_entities.erase(em.m_entities.begin()+i, em.m_entities.end());

			return p;
		}

	private:
		// Will always be in increasing id order
		std::vector<entity*> m_entities;
		uint64_t m_id = 0;

		sf::String m_name;

		game* m_game = nullptr;
	};
}

#endif