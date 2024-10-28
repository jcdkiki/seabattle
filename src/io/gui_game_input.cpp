#include "gui_game_input.hpp"

#include <SDL2/SDL.h>
#include <SDL_keycode.h>

namespace seabattle {
    inline AtomicInputMessage key2message(SDL_Keycode key)
    {
        switch (key) {
        case SDLK_w:
            return AtomicInputMessage(AtomicInputMessage::CURSOR_UP);
        case SDLK_s:
            return AtomicInputMessage(AtomicInputMessage::CURSOR_DOWN);
        case SDLK_a:
            return AtomicInputMessage(AtomicInputMessage::CURSOR_LEFT);
        case SDLK_d:
            return AtomicInputMessage(AtomicInputMessage::CURSOR_RIGHT);
        case SDLK_RETURN:
            return AtomicInputMessage(AtomicInputMessage::PRIMARY_ACTION);
        case SDLK_e:
            return AtomicInputMessage(AtomicInputMessage::SECONDARY_ACTION);
        case SDLK_q:
            return AtomicInputMessage(AtomicInputMessage::QUIT);
        default:
            return AtomicInputMessage(AtomicInputMessage::INVALID);
        }
    }

    void GUIGameInput::operator>>(Game &game)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    game << AtomicInputMessage(AtomicInputMessage::QUIT);
                    break;
                case SDL_KEYDOWN:
                    game << key2message(e.key.keysym.sym);
                    break;
            }
        }
    }
}
