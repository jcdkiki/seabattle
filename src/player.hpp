#ifndef SEABATTLE_PLAYER_HPP_
#define SEABATTLE_PLAYER_HPP_

#include "field.hpp"
#include "ship_manager.hpp"

namespace seabattle {
    struct Player {
        Field field;
        ShipManager ships;
        vec2 cursor;
        bool double_damage_flag;
    };
}

#endif
