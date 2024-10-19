#ifndef SEABATTLE_ABILITY_MANAGER_HPP_
#define SEABATTLE_ABILITY_MANAGER_HPP_

#include <memory>
#include "ability.hpp"

namespace seabattle {
    class AbilityManager {
        std::vector<std::unique_ptr<Ability>> abilities;
    public:
        AbilityManager();

        Ability &addRandomAbility(Player &player);
        Ability &getAbility();
        bool isEmpty();
        void popAbility();
    };
}

#endif
