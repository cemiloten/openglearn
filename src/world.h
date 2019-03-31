#pragma once

#include <memory>
#include <vector>

#include "component.h"
#include "transform.h"
#include "mesh.h"

class World
{
public:
    World(unsigned int entity_count);

    bool create_entity(unsigned int& index) const;
    void destroy_entity(const unsigned int index);
    void add_component(const unsigned int index, const ComponentType type);
    void add_components(const unsigned int index, const std::vector<ComponentType>& types);
    bool has_component(const unsigned int index, const ComponentType type) const;
    IComponent* get_component(const unsigned int index, const ComponentType type);

private:
    unsigned int m_entity_count;
    std::vector<unsigned int> m_entities;

    std::vector<Transform> m_transforms;
    std::vector<Mesh*> m_meshes;
};