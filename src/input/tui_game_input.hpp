#ifndef SEABATTLE_DEVICES_TUI_INPUT_DEVICE_HPP_
#define SEABATTLE_DEVICES_TUI_INPUT_DEVICE_HPP_

#include "game_input.hpp"

namespace seabattle {
    class TUIGameInput : public GameInput {
    public:
        TUIGameInput(Game &game) : GameInput(game) {}
        void handle();
    };
}

#endif
