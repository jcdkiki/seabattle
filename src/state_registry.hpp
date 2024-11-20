#ifndef STATE_REGISTRY_H
#define STATE_REGISTRY_H

#include "registry.hpp"
#include <functional>

namespace seabattle {
    class GameState;
    class Game;

    class StateRegistry : public Registry<std::function<GameState*(Game &game)>> {
        StateRegistry() = default;
    public:
        static StateRegistry &self();
    };
}

#endif
