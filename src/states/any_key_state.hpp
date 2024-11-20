#ifndef SEABATTLE_ANY_KEY_STATE_HPP_
#define SEABATTLE_ANY_KEY_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class AnyKeyState : public GameState {
    public:
        static constexpr const char *name = "AnyKey";

        AnyKeyState(Game &game);
        void handle(InputMessage message);
        std::string_view getName() const;
    };
}

#endif
