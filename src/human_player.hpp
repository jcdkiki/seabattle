#ifndef SEABATTLE_HUMAN_PLAYER_HPP_
#define SEABATTLE_HUMAN_PLAYER_HPP_

#include "messaging/message_generator.hpp"
#include "player.hpp"
#include "abilities/ability_manager.hpp"

namespace seabattle {
    struct HumanPlayer : public Player, public MessageGenerator {
        AbilityManager abilities;

        HumanPlayer() {}
        void useAbility(Player &target);
        void attack(Player &target);
    };
}

#endif
