#ifndef SEABATTLE_CONTROL_SETUP_SHIPS_CONTROL_HPP_
#define SEABATTLE_CONTROL_SETUP_SHIPS_CONTROL_HPP_

#include "game_control.hpp"
#include "messaging/game_messages.hpp"

namespace seabattle {
    class SetupShipsControl : public GameControl {
        int size;
        std::vector<size_t> ship_sizes;
    public:
        SetupShipsControl(GameState &state);
        void handleInput(std::unique_ptr<const InputMessage> msg);
    };
}

#endif
