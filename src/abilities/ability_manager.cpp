#include "ability_manager.hpp"
#include "ability_registry.hpp"
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

namespace seabattle {
    AbilityManager::AbilityManager()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        std::vector<const AbilityRegistry::Entry*> entries;
        for (const auto &entry : registry) {
            entries.emplace_back(&entry);
        }
        
        std::shuffle(entries.begin(), entries.end(), std::default_random_engine(time(NULL)));

        for (AbilityRegistry::Entry entry = registry.begin(); entry != registry.end(); entry++) {
            abilities.push(entry);
        }
    }

    const char *AbilityManager::addRandomAbility()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        AbilityRegistry::Entry entry = registry.begin();
        for (size_t i = (rand() % registry.count()); i > 0; i--)
            entry++;

        abilities.push(entry);
        return entry->first;
    }

    const AbilityRegistry::Entry &AbilityManager::top()
    {
        if (this->empty()) {
            throw NoAbilitiesException();
        }

        return abilities.front();
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
