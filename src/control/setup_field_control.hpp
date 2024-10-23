#ifndef SEABATTLE_SETUP_FIELD_CONTROL_HPP_
#define SEABATTLE_SETUP_FIELD_CONTROL_HPP_

#include "game_control.hpp"
#include "messaging/game_messages.hpp"

namespace seabattle {
    class SetupFieldControl : public GameControl {
        vec2 size;
    public:
        SetupFieldControl(GameState &state);
        void handleInput(std::unique_ptr<const InputMessage> msg);
    };
}

#endif
