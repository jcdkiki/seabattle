#ifndef SEABATTLE_INPUT_MESSAGES_HPP_
#define SEABATTLE_INPUT_MESSAGES_HPP_

#include "vec2.hpp"
#include "ship.hpp"
#include <string>

namespace seabattle {
    class Field;
    class GameState;

    struct Message {
        virtual ~Message() {}
    };

    struct InputMessage : public Message {
        enum Action {
            CURSOR_LEFT,
            CURSOR_RIGHT,
            CURSOR_UP,
            CURSOR_DOWN,
            PRIMARY_ACTION,
            SECONDARY_ACTION,
            BACK,
            INVALID
        };

        Action action;
        InputMessage(Action action) : action(action) {}
    };

    struct RenderFieldMessage : public Message {
        enum Location {
            LEFT,
            RIGHT
        };
        
        Location location;
        const Field &field;
        bbox2 cursor;

        RenderFieldMessage(Location location, const Field &field, bbox2 cursor) : location(location), field(field), cursor(cursor) {}
    };

    struct LogMessage : public Message {
        std::string text;

        LogMessage(std::string text) : text(text) {}
    };

    struct ChangeStateMessage : public Message {
        GameState *new_state;

        ChangeStateMessage(GameState *new_state) : new_state(new_state) {}
    };
}

#endif
