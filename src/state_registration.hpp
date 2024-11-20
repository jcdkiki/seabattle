#ifndef STATE_REGISTRATION_H
#define STATE_REGISTRATION_H

#include "state_registry.hpp"

namespace seabattle {
    class Game;

    template<class T>
    class StateRegistration {
        static bool is_registered;

        static T* createInstance(Game &game) { return new T(game); }
    public:
        StateRegistration()
        {
            static bool is_registered = StateRegistry::self().add(
                T::name,
                StateRegistry::Info(createInstance)
            );
        }
    };
}

#endif
