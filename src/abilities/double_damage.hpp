#ifndef SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_
#define SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_

#include "ability.hpp"
#include "player.hpp"

namespace seabattle {
    class DoubleDamage : public Ability {
        Player &user;
    public:
        static constexpr const char *name = "Double Damage";

        DoubleDamage(Player &user, Player &target) : user(user) {}
        void use();
        void renderBy(GameRenderer &renderer) const;
    };
}

#endif
