#ifndef SEABATTLE_PLAYER_ACTION_STATE_HPP_
#define SEABATTLE_PLAYER_ACTION_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class PlayerActionState : public GameState {
        void attack();
        void useAbility();
        void mark();
        void move(InputMessage message);
    
    public:
        static constexpr const char *name = "PlayerAction";

        PlayerActionState(Game &game);
        void handle(InputMessage message);
        std::string_view getName() const;
    };
}

#endif
