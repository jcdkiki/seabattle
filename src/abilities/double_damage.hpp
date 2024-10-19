#ifndef SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_
#define SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_

#include "ability.hpp"

namespace seabattle {
    class DoubleDamage : public Ability {
    public:
        void use(Player &user);
        const char *getName();
    };
}

#endif
