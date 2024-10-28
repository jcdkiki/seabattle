#ifndef SEABATTLE_CONTROL_FIGHT_STATE_HPP_
#define SEABATTLE_CONTROL_FIGHT_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class FightState : public GameState {
    public:
        FightState(Game &ctx);
        void operator<<(AtomicInputMessage message);
    };
}

#endif
