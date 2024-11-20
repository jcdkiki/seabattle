#ifndef SEABATTLE_GUI_GAME_INPUT_HPP_
#define SEABATTLE_GUI_GAME_INPUT_HPP_

#include "game_input.hpp"
#include "gui/controls.hpp"

namespace seabattle {
    class GUIGameInput : public GameInput {
        GUIControls controls;
    public:
        GUIGameInput(Game &game);
        void handle();
    };
}

#endif
