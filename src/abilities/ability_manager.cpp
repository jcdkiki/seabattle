#include "ability_manager.hpp"
#include "ability.hpp"
#include <random>
#include <vector>
#include <algorithm>

namespace seabattle {
    AbilityManager::AbilityManager()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        std::vector<AbilityRegistry::FactoryFn> factories;
        for (auto entry : registry) {
            factories.push_back(entry.factory);
        }
        std::shuffle(factories.begin(), factories.end(), std::default_random_engine(time(NULL)));

        for (auto factory : factories) {
            abilities.push(factory);
        }
    }

    const char *AbilityManager::addRandomAbility()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        const AbilityRegistry::Entry &entry = *(registry.begin() + (rand() % registry.count())); 
        abilities.push(entry.factory);
        return entry.name;
    }

    AbilityRegistry::FactoryFn AbilityManager::top()
    {
        if (this->empty()) {
            throw NoAbilitiesException();
        }

        auto res = abilities.front();
        return res;
    }

    void AbilityManager::pop()
    {
        if (this->empty()) {
            throw NoAbilitiesException();
        }

        abilities.pop();
    }

    bool AbilityManager::empty()
    {
        return abilities.size() == 0;
    }
}
