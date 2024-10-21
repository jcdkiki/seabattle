#include "gui_input_device.hpp"
#include "messaging/input_messages.hpp"

#include <SDL2/SDL.h>
#include <SDL_keycode.h>

namespace seabattle {
    inline InputMessage::Action key2message(SDL_Keycode key)
    {
        switch (key) {
        case SDLK_w:
            return InputMessage::CURSOR_UP;
        case SDLK_s:
            return InputMessage::CURSOR_DOWN;
        case SDLK_a:
            return InputMessage::CURSOR_LEFT;
        case SDLK_d:
            return InputMessage::CURSOR_RIGHT;
        case SDLK_RETURN:
            return InputMessage::PRIMARY_ACTION;
        case SDLK_e:
            return InputMessage::SECONDARY_ACTION;
        case SDLK_q:
            return InputMessage::BACK;
        default:
            return InputMessage::INVALID;
        }
    }

    void GUIInputDevice::update()
    {
        SDL_Event e;

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    emplace<InputMessage>(InputMessage::BACK);
                    break;
                case SDL_KEYDOWN:
                    emplace<InputMessage>(key2message(e.key.keysym.sym));
                    break;
            }
        }
    }
}
