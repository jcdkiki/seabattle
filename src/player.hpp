#ifndef SEABATTLE_PLAYER_HPP_
#define SEABATTLE_PLAYER_HPP_

#include "field.hpp"
#include "ship_manager.hpp"
#include "ability_manager.hpp"
#include <memory>

namespace seabattle {
    class Game;

    struct Player {
        Field field;
        ShipManager ships;
        vec2 cursor;
        bool double_damage_flag;
        AbilityManager abilities;

        std::shared_ptr<Ability> useAbility(Player &target);
        Field::AttackResult attack(Player &target);

        friend std::ostream &operator<<(std::ostream &os, Player &player);
        friend std::istream &operator>>(std::istream &is, Player &player);
    };
}

#endif
