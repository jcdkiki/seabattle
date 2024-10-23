#include "human_player.hpp"
#include "messaging/render_messages.hpp"

namespace seabattle {
    void HumanPlayer::useAbility(Player &target)
    {
        auto ability = abilities.top()(*this, target);
        ability->use(); // can throw
        abilities.pop();
        while (!ability->empty()) {
            push(std::move(ability->pop()));
        }
    }

    void HumanPlayer::attack(Player &target)
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
}
