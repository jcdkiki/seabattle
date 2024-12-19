#ifndef SEABATTLE_GUI_CONTROLS_HPP_
#define SEABATTLE_GUI_CONTROLS_HPP_

#include "input/input_messages.hpp"
#include <SDL2/SDL_keycode.h>
#include <istream>
#include <unordered_map>

namespace seabattle {
    class GUIControls {
        std::unordered_map<SDL_Keycode, InputMessage*> mapping;

    public:
        GUIControls();
        InputMessage *keyCodeToMessage(SDL_Keycode keycode);

        friend std::istream &operator>>(std::istream &is, GUIControls &controls);
    };
}

#endif
