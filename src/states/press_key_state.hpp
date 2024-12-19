#ifndef SEABATTLE_ANY_KEY_STATE_HPP_
#define SEABATTLE_ANY_KEY_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class PressKeyState : public GameState {
    public:
        static constexpr const char *name = "PressKey";

        PressKeyState(Game &game);
        void primaryAction();
        std::string_view getName() const;
    };
}

#endif
