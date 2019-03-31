#include "world.h"

World::World(unsigned int entity_count)
    : m_entity_count(entity_count)
{
    m_entities.resize(entity_count);
    m_transforms.resize(entity_count);;
    m_meshes.resize(entity_count);;
}

bool World::create_entity(unsigned int& index) const
{
    // unsigned int size = m_entities.size();
    // for (unsigned int i = 0; i < size; ++i) {
    //     if (m_entities[i] == 0) {
    //         index = i;
    //         return true;
    //     }
    // }
    // index = size;
    // return false;
}

void World::destroy_entity(const unsigned int index)
{
    m_entities[index] = 0; // Sets all component flags to 0
}

bool World::has_component(const unsigned int index, const ComponentType type) const
{
    unsigned int uint_type = static_cast<unsigned int>(type);
    return (m_entities[index] & uint_type) == uint_type;
}

void World::add_component(const unsigned int index, const ComponentType type)
{
    m_entities[index] |= static_cast<unsigned int>(type);
}

void World::add_components(const unsigned int index, const std::vector<ComponentType>& types)
{
    unsigned int entity = 0;
    for (int i = 0; i < types.size(); ++i) {
        entity |= static_cast<unsigned int>(types[i]);
    }
    m_entities[index] |= entity;
}

IComponent* World::get_component(const unsigned int index, const ComponentType type)
{
    // switch (type) {
    //     case ComponentType::Transform:
    //         return &m_transforms[index];
    //     case ComponentType::Mesh:
    //         return m_meshes[index];
    //     default:
    //         return nullptr;
    // }
}