#include "gui_game_input.hpp"
#include "input/message.hpp"

#include <SDL2/SDL.h>
#include <SDL_keycode.h>
#include <fstream>

namespace seabattle {
    void GUIGameInput::handle()
    {
        SDL_Event e;

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    game.handle(InputMessage(InputMessage::QUIT));
                    break;
                case SDL_KEYDOWN:
                    game.handle(controls.keyCodeToMessage(e.key.keysym.sym));
                    break;
            }
        }
    }

    GUIGameInput::GUIGameInput(Game &game) : GameInput(game)
    {
        std::ifstream file("data/controls.cfg");
        file >> controls;
        file.close();
    }
}
