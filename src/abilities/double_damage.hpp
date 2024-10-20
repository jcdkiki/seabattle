#ifndef SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_
#define SEABATTLE_ABILITIES_DOUBLE_DAMAGE_HPP_

#include "ability.hpp"

namespace seabattle {
    class DoubleDamage : public IAbility {
        bool &double_damage_flag;
    public:
        DoubleDamage(Player &user) : double_damage_flag(user.double_damage_flag) {}
        void use();
    };
}

#endif
