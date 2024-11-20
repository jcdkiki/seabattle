#ifndef ABILITY_REGISTRATION_H
#define ABILITY_REGISTRATION_H

#include "ability_registry.hpp"

namespace seabattle {
    template<class T>
    class AbilityRegistration {
        static bool is_registered;

        static T* createInstance(Player &user, Player &target) { return new T(user, target); }
public:
        AbilityRegistration()
        {
            static bool is_registered = AbilityRegistry::self().add(
                T::name,
                AbilityRegistry::Info(createInstance)
            );
        }
    };
}

#endif // ABILITY_REGISTRATION_H
