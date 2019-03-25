#include "world.h"

World::World(unsigned int entity_count)
    : m_entity_count(entity_count)
{
    m_entities.resize(entity_count);
}

unsigned int World::create_entity(std::unique_ptr<World> world)
{
    unsigned int entity;
    unsigned int entity_count = world->m_entity_count;
    for (entity = 0; entity < entity_count; ++entity) {
        if (world->m_entities[entity] == CompTypeNone) {
            return entity;
        }
    }
    return entity_count;
}

void World::destroy_entity(std::unique_ptr<World> world, unsigned int index)
{
    world->m_entities[index] = CompTypeNone;
}