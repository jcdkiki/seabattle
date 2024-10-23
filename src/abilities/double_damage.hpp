#ifndef SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_
#define SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_

#include "ability.hpp"

namespace seabattle {
    class DoubleDamage : public Ability {
        Player &user;
    public:
        DoubleDamage(Player &user) : user(user) {}
        void use();
    };
}

#endif
