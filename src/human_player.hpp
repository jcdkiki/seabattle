#ifndef SEABATTLE_HUMAN_PLAYER_HPP_
#define SEABATTLE_HUMAN_PLAYER_HPP_

#include "messaging/render_messages.hpp"
#include "messaging/message_generator.hpp"
#include "player.hpp"
#include "abilities/ability_manager.hpp"
#include <stdexcept>

namespace seabattle {
    struct HumanPlayer : public Player, public MessageGenerator {
        AbilityManager abilities;

        HumanPlayer(Player &opponent) : abilities(*this, opponent) {}

        void useAbility(Player &target)
        {
            if (abilities.empty()) {
                throw std::invalid_argument("You don't have any abilities");
            }

            auto ability = abilities.pop()(*this, target);
            ability->use();
            while (!ability->empty()) {
                push(std::move(ability->pop()));
            }
        }

        void attack(Player &target)
        {
            bool ok = target.field.attack(cursor, false);
            if (double_damage_flag) {
                ok |= target.field.attack(cursor, false);
                double_damage_flag = false;
            }

            if (ok && target.field[cursor].ship_segment.getShip().isDestroyed()) {
                const char *name = abilities.addRandomAbility();
                emplace<LogMessage>(std::string("New ability: ") + name);
            }
        }
    };
}

#endif
