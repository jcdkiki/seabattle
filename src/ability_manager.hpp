#ifndef SEABATTLE_ABILITY_MANAGER_HPP_
#define SEABATTLE_ABILITY_MANAGER_HPP_

#include "ability_registry.hpp"
#include "exception.hpp"
#include <deque>
#include <string_view>

namespace seabattle {
    class AbilityManager {
    public:
        struct AbilityData {
            std::string_view name;
            AbilityRegistry::Info info;
        };

    private:
        std::deque<AbilityData> abilities;
    public:
        AbilityManager();

        void addRandomAbility();
        void addAbility(std::string_view name);
        bool empty();
        const AbilityData &top();
        void pop();

        typedef std::deque<AbilityData>::iterator Iterator;
        inline Iterator begin() { return abilities.begin(); }
        inline Iterator end() { return abilities.end(); }
        inline size_t count() { return abilities.size(); }
    };

    class NoAbilitiesException : public SeabattleException {
    public:
        const char *what() { return "You have no abilities"; }
    };
}

#endif
