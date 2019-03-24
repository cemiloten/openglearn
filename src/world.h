#pragma once

#include <memory>
#include <vector>
#include "position_component.h"

#include "types.h"

class World
{
public:
    World(u32 entity_count);

    static u32 create_entity(std::unique_ptr<World> world);
    static void destroy_entity(std::unique_ptr<World> world, u32 index);

private:
    u32 m_entity_count;

    std::vector<u32> m_entities;
    // std::vector<PositionComponent> m_positions;
    // std::vector<QuaternionComponent> m_rotations;
}