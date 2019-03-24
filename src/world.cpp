#include "world.h"

World::World(u32 entity_count)
    : m_entity_count(entity_count)
{
    m_entities.resize(entity_count);
}

u32 World::create_entity(std::unique_ptr<World> world)
{
    u32 entity;
    u32 entity_count = world->m_entity_count;
    for (entity = 0; entity < entity_count; ++entity) {
        if (world->m_entities[entity] == CompTypeNone) {
            return entity;
        }
    }
    return entity_count;
}

void World::destroy_entity(std::unique_ptr<World> world, u32 index)
{
    world->m_entities[index] = CompTypeNone;
}