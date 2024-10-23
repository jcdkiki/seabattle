#ifndef SEABATTLE_CONTROL_FIGHT_CONTROL_HPP_
#define SEABATTLE_CONTROL_FIGHT_CONTROL_HPP_

#include "game_control.hpp"

namespace seabattle {
    class FightControl : public GameControl {
    public:
        FightControl(GameState &state);
        void handleInput(std::unique_ptr<const InputMessage> msg);
    };
}

#endif
