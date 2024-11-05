#include "human_player.hpp"
#include <memory>

namespace seabattle {
    void HumanPlayer::useAbility(Player &target)
    {
        std::unique_ptr<Ability> ability(abilities.top()->second.generator(*this, target));
        ability->use(); // can throw
        abilities.pop();
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
            //emplace<LogMessage>(std::string("New ability: ") + name);
        }
    }
}
