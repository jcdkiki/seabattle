#include "ability_manager.hpp"
#include "ability.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>

namespace seabattle {
    AbilityManager::AbilityManager()
    {
        AbilityFactory &factory = AbilityFactory::getInstance();
        size_t size = factory.getSize();
        for (size_t i = 0; i < size; i++) {
            abilities.emplace_back(factory.getGenerator(i)());
        }

        std::shuffle(abilities.begin(), abilities.end(), std::default_random_engine(time(NULL)));
    }

    Ability &AbilityManager::addRandomAbility(Player &player)
    {
        AbilityFactory &factory = AbilityFactory::getInstance();
        size_t index = rand() % factory.getSize();
        Ability *ability = factory.getGenerator(index)();
        
        abilities.emplace_back(ability);
        return *ability;
    }

    Ability &AbilityManager::getAbility()
    {
        if (isEmpty()) {
            throw std::runtime_error("AbilityManager`s queue is empty");
        }

        return *abilities.front().get();
    }

    void AbilityManager::popAbility()
    {
        if (isEmpty()) {
            throw std::runtime_error("AbilityManager`s queue is empty");
        }

        abilities.erase(abilities.begin());
    }

    bool AbilityManager::isEmpty()
    {
        return abilities.size() == 0;
    }
}
