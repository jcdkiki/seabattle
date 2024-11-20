#include "controls.hpp"
#include "input/message.hpp"
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <iostream>
#include <unordered_map>

namespace seabattle {
    InputMessage GUIControls::keyCodeToMessage(SDL_Keycode keycode)
    {
        auto iterator = mapping.find(keycode);
        if (iterator == mapping.end()) {
            return InputMessage(InputMessage::INVALID);
        }

        return iterator->second;
    }

    static std::unordered_map<std::string_view, InputMessage::Kind> str_to_kind = {
        { "primary", InputMessage::Kind::PRIMARY_ACTION },
        { "secondary", InputMessage::Kind::SECONDARY_ACTION },
        { "tertiary", InputMessage::Kind::TERTIARY_ACTION },
        { "quit", InputMessage::Kind::QUIT },
        { "left", InputMessage::Kind::CURSOR_LEFT },
        { "right", InputMessage::Kind::CURSOR_RIGHT },
        { "up", InputMessage::Kind::CURSOR_UP },
        { "down", InputMessage::Kind::CURSOR_DOWN },
        { "save", InputMessage::Kind::SAVE },
        { "load", InputMessage::Kind::LOAD }
    };

    static std::unordered_map<SDL_Keycode, InputMessage::Kind> defaults = {
        { SDLK_RETURN, InputMessage::Kind::PRIMARY_ACTION },
        { SDLK_e, InputMessage::Kind::SECONDARY_ACTION  },
        { SDLK_r, InputMessage::Kind::TERTIARY_ACTION },
        { SDLK_ESCAPE, InputMessage::Kind::QUIT },
        { SDLK_a, InputMessage::Kind::CURSOR_LEFT },
        { SDLK_d, InputMessage::Kind::CURSOR_RIGHT },
        { SDLK_w, InputMessage::Kind::CURSOR_UP },
        { SDLK_s, InputMessage::Kind::CURSOR_DOWN },
        { SDLK_F1, InputMessage::Kind::SAVE },
        { SDLK_F2, InputMessage::Kind::LOAD }
    };

    GUIControls::GUIControls() : mapping(defaults) {}

    std::istream &operator>>(std::istream &is, GUIControls &controls)
    {
        std::unordered_map<SDL_Keycode, InputMessage::Kind> mapping;
        std::unordered_map<InputMessage::Kind, SDL_Keycode> inversed_mapping;

        std::string str1, str2;
        while (is >> str1) {
            auto iterator = str_to_kind.find(str1.c_str());
            if (iterator == str_to_kind.end()) {
                std::cerr << "Unknown setting: '" << str1 << "'" << std::endl; 
                break;
            }
            InputMessage::Kind kind = iterator->second;
            
            is >> str2;
            if (is.fail()) {
                break;
            }

            SDL_Keycode keycode = SDL_GetKeyFromName(str2.c_str());
            if (keycode == SDLK_UNKNOWN) {
                std::cerr << "Unknown keycode: '" << str2 << "'" << std::endl;
                break;
            }

            if (inversed_mapping.find(kind) != inversed_mapping.end()) {
                std::cerr << "Setting '" << str1 << "' is already set" << std::endl;
                break;
            }

            if (mapping.find(keycode) != mapping.end()) {
                std::cerr << "Keycode '" << str2 << "' is already bound" << std::endl;
                break;
            }

            inversed_mapping[kind] = keycode;
            mapping[keycode] = kind;
        }

        if (!is.eof() || controls.mapping.size() != InputMessage::TOTAL_MESSAGES) {
            is.setstate(is.failbit);    
        }
        else {
            controls.mapping = std::move(mapping);
        }

        return is;
    }
}
