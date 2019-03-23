#include "world.h"

World::World(unsigned int entity_count)
    : m_entity_count(entity_count)
{
    m_entities.resize(entity_count);
}

unsigned int World::create_entity(unique_ptr<World> world)
{
    unsigned int entity;
    for (entity = 0; entity < world->m_entity_count; ++entity) {

    }
}