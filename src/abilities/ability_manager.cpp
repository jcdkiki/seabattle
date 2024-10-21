#include "ability_manager.hpp"
#include "ability.hpp"
#include <random>
#include <algorithm>

namespace seabattle {
    AbilityManager::AbilityManager(Player &user, Player &target)
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        for (auto entry : registry) {
            abilities.push_back(entry.factory);
        }
        std::shuffle(abilities.begin(), abilities.end(), std::default_random_engine(time(NULL)));
    }

    const char *AbilityManager::addRandomAbility()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        const AbilityRegistry::Entry &entry = *(registry.begin() + (rand() % registry.count())); 
        abilities.push_back(entry.factory);
        return entry.name;
    }

    AbilityRegistry::FactoryFn AbilityManager::pop()
    {
        if (this->empty()) {
            throw std::runtime_error("AbilityManager`s queue is empty");
        }

        auto res = abilities.front();
        abilities.erase(abilities.begin());
        return res;
    }

    bool AbilityManager::empty()
    {
        return abilities.size() == 0;
    }
}
