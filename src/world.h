#pragma once

#include <memory>
#include <vector>
#include "position_component.h"

class World
{
public:
    World(unsigned int entity_count);

    static unsigned int create_entity(std::unique_ptr<World> world);
    static void destroy_entity(std::unique_ptr<World> world, unsigned int index);

private:
    unsigned int m_entity_count;

    std::vector<unsigned int> m_entities;
    // std::vector<PositionComponent> m_positions;
    // std::vector<QuaternionComponent> m_rotations;
};