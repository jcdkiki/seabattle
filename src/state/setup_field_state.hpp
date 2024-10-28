#ifndef SEABATTLE_SETUP_FIELD_STATE_HPP_
#define SEABATTLE_SETUP_FIELD_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class SetupFieldState : public GameState {
        vec2 size;
    public:
        SetupFieldState(Game &ctx);
        void operator<<(AtomicInputMessage message);
    };
}

#endif
