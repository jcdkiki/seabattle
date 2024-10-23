#ifndef SEABATTLE_ABILITY_MANAGER_HPP_
#define SEABATTLE_ABILITY_MANAGER_HPP_

#include "ability.hpp"
#include "exception.hpp"

namespace seabattle {
    class AbilityManager {
        std::queue<AbilityRegistry::FactoryFn> abilities;
    public:
        AbilityManager();

        const char *addRandomAbility();
        bool empty();
        AbilityRegistry::FactoryFn top();
        void pop();
    };

    class NoAbilitiesException : public SeabattleException {
    public:
        const char *what() { return "You have no abilities"; }
    };
}

#endif
