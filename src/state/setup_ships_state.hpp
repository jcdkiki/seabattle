#ifndef SEABATTLE_CONTROL_SETUP_SHIPS_STATE_HPP_
#define SEABATTLE_CONTROL_SETUP_SHIPS_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class SetupShipsState : public GameState {
        int size;
        std::vector<size_t> ship_sizes;
    public:
        SetupShipsState(Game &ctx);
        void operator<<(AtomicInputMessage message);
    };
}

#endif
