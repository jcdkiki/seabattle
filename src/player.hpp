#ifndef SEABATTLE_PLAYER_HPP_
#define SEABATTLE_PLAYER_HPP_

#include "field.hpp"
#include "message_pipe.hpp"
#include "ship_manager.hpp"
#include "abilities/ability_manager.hpp"

namespace seabattle {
    class Game;

    struct Player : public MessagePipe<Game> {
        struct RenderAbilityMessage {
            AbilityRegistry::AbilityInfo info;
            const Ability &ability;
        };

        Field field;
        ShipManager ships;
        vec2 cursor;
        bool double_damage_flag;
        AbilityManager abilities;

        Player(Game &game) : MessagePipe(game) {}
        void useAbility(Player &target);
        void attack(Player &target);
    };
}

#endif
