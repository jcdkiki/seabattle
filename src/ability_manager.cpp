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
        std::vector<AbilityData> entries;
        for (const auto &entry : registry) {
            entries.push_back({ entry.first, entry.second });
        }
        
        std::shuffle(entries.begin(), entries.end(), std::default_random_engine(time(NULL)));

        for (auto entry : entries) {
            abilities.push_back(entry);
        }
    }

    void AbilityManager::addRandomAbility()
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        AbilityRegistry::Entry entry = registry.begin();
        for (size_t i = (rand() % registry.count()); i > 0; i--)
            entry++;

        abilities.push_back({ entry->first, entry->second });
    }

    const AbilityManager::AbilityData &AbilityManager::top()
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

        abilities.pop_front();
    }

    bool AbilityManager::empty()
    {
        return abilities.size() == 0;
    }

    void AbilityManager::addAbility(std::string_view name)
    {
        AbilityRegistry &registry = AbilityRegistry::self();
        AbilityRegistry::Entry entry = registry.find(name.data());
        abilities.push_back({ entry->first, entry->second });
    }
}
