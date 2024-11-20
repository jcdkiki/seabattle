#ifndef SEABATTLE_SETUP_FIELD_STATE_HPP_
#define SEABATTLE_SETUP_FIELD_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class SetupFieldState : public GameState {
        vec2 size;

    public:
        static constexpr const char *name = "SetupField";

        SetupFieldState(Game &game);
        void handle(InputMessage message);
        std::string_view getName() const;
    };
}

#endif
