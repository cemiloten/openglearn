#pragma once

#include <memory>
#include <vector>
#include "position_component.h"

class World
{
public:
    World(unsigned int entity_count);

    static unsigned int create_entity(unique_ptr<World> world);

private:
    std::vector<unsigned int> m_entities;
    unsigned int m_entity_count;
    // std::vector<PositionComponent> m_positions;
    // std::vector<QuaternionComponent> m_rotations;
}