#include "gui_game_input.hpp"
#include "input/input_messages.hpp"

#include <SDL2/SDL.h>
#include <SDL_keycode.h>
#include <fstream>

namespace seabattle {
    InputMessage *GUIGameInput::pollMessage()
    {
        SDL_Event e;

        if (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    return new QuitMessage();
                case SDL_KEYDOWN:
                    return controls.keyCodeToMessage(e.key.keysym.sym);
            }
        }

        return nullptr;
    }

    GUIGameInput::GUIGameInput()
    {
        std::ifstream file("data/controls.cfg");
        file >> controls;
        file.close();
    }
}
