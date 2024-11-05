#ifndef ABILITY_REGISTRATION_H
#define ABILITY_REGISTRATION_H

#include "ability_registry.hpp"
#include "game_renderer.hpp"

namespace seabattle {
    template<class T>
    class AbilityRegistration {
        static bool is_registered;

        static T* createInstance(Player &user, Player &target) { return new T(user, target); }
        static void render(GameRenderer &renderer, const Ability &ability) { renderer << static_cast<const T&>(ability); }

public:
        AbilityRegistration(const char *name)
        {
            static bool is_registered = AbilityRegistry::self().add(
                name,
                AbilityRegistry::AbilityInfo(createInstance, render)
            );
        }
    };
}

#endif // ABILITY_REGISTRATION_H
