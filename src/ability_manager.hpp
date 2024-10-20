#ifndef SEABATTLE_ABILITY_MANAGER_HPP_
#define SEABATTLE_ABILITY_MANAGER_HPP_

#include <vector>
#include "ability.hpp"
#include "player.hpp"

namespace seabattle {
    class AbilityManager {
        std::vector<AbilityRegistry::FactoryFn> abilities;
    public:
        AbilityManager(Player &user, Player &target);

        const char *addRandomAbility();
        bool empty();
        AbilityRegistry::FactoryFn pop();
    };
}

#endif
