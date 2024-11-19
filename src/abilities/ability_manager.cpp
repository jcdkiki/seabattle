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
        std::vector<AbilityRegistry::AbilityInfo> infos;
        for (const auto &entry : registry) {
            infos.push_back(entry.second);
        }
        
        std::shuffle(infos.begin(), infos.end(), std::default_random_engine(time(NULL)));

        for (auto info : infos) {
            abilities.push(info);
        }
    }

    const char *AbilityManager::addRandomAbility()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        AbilityRegistry::Entry entry = registry.begin();
        for (size_t i = (rand() % registry.count()); i > 0; i--)
            entry++;

        abilities.push(entry->second);
        return entry->first;
    }

    const AbilityRegistry::AbilityInfo &AbilityManager::top()
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
