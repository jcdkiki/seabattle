#include "player.hpp"
#include <memory>

namespace seabattle {
    void Player::useAbility(Player &target)
    {
        auto info = abilities.top();
        std::unique_ptr<Ability> ability(info.generator(*this, target));
        ability->use(); // can throw
        (*this) << RenderAbilityMessage { .info = info, .ability = *ability };
        abilities.pop();
    }

    void Player::attack(Player &target)
    {
        bool ok = target.field.attack(cursor, false);
        if (double_damage_flag) {
            ok |= target.field.attack(cursor, false);
            double_damage_flag = false;
        }

        if (ok && target.field[cursor].ship_segment.getShip().isDestroyed()) {
            const char *name = abilities.addRandomAbility();
            (*this) << (std::string("New ability: ") + name);
        }
    }
}
