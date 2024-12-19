#ifndef SEABATTLE_PLAYER_ACTION_STATE_HPP_
#define SEABATTLE_PLAYER_ACTION_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class PlayerActionState : public GameState {
    public:
        static constexpr const char *name = "PlayerAction";

        void primaryAction();
        void secondaryAction();
        void tertiaryAction();
        void moveCursor(vec2 amount);

        PlayerActionState(Game &game);
        std::string_view getName() const;
    };
}

#endif
