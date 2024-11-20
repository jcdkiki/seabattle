#ifndef ABILITY_REGISTRY_H
#define ABILITY_REGISTRY_H

#include "registry.hpp"
#include "abilities/ability.hpp"
#include <functional>

namespace seabattle {
    class Player;
    class GameRenderer;

    class AbilityRegistry : public Registry<std::function<Ability*(Player &user, Player &target)>> {
        AbilityRegistry() = default;
    public:
        static AbilityRegistry &self();
    };
}

#endif // ABILITY_REGISTRY_H
