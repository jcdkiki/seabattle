#ifndef SEABATTLE_GUI_GAME_INPUT_HPP_
#define SEABATTLE_GUI_GAME_INPUT_HPP_

#include "game_input.hpp"

namespace seabattle {
    class GUIGameInput : public GameInput {
    public:
        void operator>>(Game &game);
    };
}

#endif
