#include "controls.hpp"
#include "input/input_messages.hpp"
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <memory>
#include <iostream>
#include <unordered_map>

namespace seabattle {
    InputMessage *GUIControls::keyCodeToMessage(SDL_Keycode keycode)
    {
        auto iterator = mapping.find(keycode);
        if (iterator == mapping.end()) {
            return nullptr;
        }

        return iterator->second->copy();
    }

    static std::unordered_map<std::string_view, std::shared_ptr<InputMessage>> messages = {
        { "primary", std::make_unique<PrimaryActionMessage>() },
        { "secondary", std::make_unique<SecondaryActionMessage>() },
        { "tertiary", std::make_unique<TertiaryActionMessage>() },
        { "quit", std::make_unique<QuitMessage>() },
        { "save", std::make_unique<SaveMessage>() },
        { "load", std::make_unique<LoadMessage>() },
        { "up", std::make_unique<MoveCursorMessage>(vec2(0, -1)) },
        { "down", std::make_unique<MoveCursorMessage>(vec2(0, 1)) },
        { "left", std::make_unique<MoveCursorMessage>(vec2(-1, 0)) },
        { "right", std::make_unique<MoveCursorMessage>(vec2(1, 0)) },
    };
    
    static std::unordered_map<SDL_Keycode, InputMessage*> defaults = {
        { SDLK_RETURN, messages["primary"].get() },
        { SDLK_e, messages["secondary"].get() },
        { SDLK_r, messages["tertiary"].get() },
        { SDLK_ESCAPE, messages["quit"].get() },
        { SDLK_a, messages["left"].get() },
        { SDLK_d, messages["right"].get() },
        { SDLK_w, messages["up"].get() },
        { SDLK_s, messages["down"].get() },
        { SDLK_F1, messages["save"].get() },
        { SDLK_F2, messages["load"].get() },
    };

    GUIControls::GUIControls() : mapping(defaults) {}

    std::istream &operator>>(std::istream &is, GUIControls &controls)
    {
        std::unordered_map<SDL_Keycode, InputMessage*> mapping;
        std::unordered_map<InputMessage*, SDL_Keycode> inversed_mapping;

        std::string str1, str2;
        while (is >> str1) {
            auto iterator = messages.find(str1.c_str());
            
            if (iterator == messages.end()) {
                std::cerr << "Unknown command: '" << str1 << "'" << std::endl;
                break;
            }

            InputMessage *msg = iterator->second.get();
            
            is >> str2;
            if (is.fail()) {
                break;
            }

            SDL_Keycode keycode = SDL_GetKeyFromName(str2.c_str());
            if (keycode == SDLK_UNKNOWN) {
                std::cerr << "Unknown keycode: '" << str2 << "'" << std::endl;
                break;
            }

            if (inversed_mapping.find(msg) != inversed_mapping.end()) {
                std::cerr << "Command '" << str1 << "' is already set" << std::endl;
                break;
            }

            if (mapping.find(keycode) != mapping.end()) {
                std::cerr << "Keycode '" << str2 << "' is already bound" << std::endl;
                break;
            }

            inversed_mapping[msg] = keycode;
            mapping[keycode] = msg;
        }

        if (!is.eof() || controls.mapping.size() != defaults.size()) {
            is.setstate(is.failbit);    
        }
        else {
            controls.mapping = std::move(mapping);
        }

        return is;
    }
}
