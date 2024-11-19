#ifndef SEABATTLE_ABILITY_MANAGER_HPP_
#define SEABATTLE_ABILITY_MANAGER_HPP_

#include "ability_registry.hpp"
#include "exception.hpp"
#include <queue>

namespace seabattle {
    class AbilityManager {
        std::queue<AbilityRegistry::AbilityInfo> abilities;
    public:
        AbilityManager();

        const char *addRandomAbility();
        bool empty();
        const AbilityRegistry::AbilityInfo &top();
        void pop();
    };

    class NoAbilitiesException : public SeabattleException {
    public:
        const char *what() { return "You have no abilities"; }
    };
}

#endif
