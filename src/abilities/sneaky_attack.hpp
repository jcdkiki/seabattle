#ifndef SEABATTLE_ABILITIES_SNEAKY_ATTACK_HPP_
#define SEABATTLE_ABILITIES_SNEAKY_ATTACK_HPP_

#include "ability.hpp"

namespace seabattle {
    class SneakyAttack : public Ability {
    public:
        void use(Player &user);
        const char *getName();
    };
}

#endif
