#ifndef SEABATTLE_INPUT_MESSAGES_HPP_
#define SEABATTLE_INPUT_MESSAGES_HPP_

#include "vec2.hpp"
#include "field.hpp"
#include <memory>
#include <string>

namespace seabattle {
    class GameControl;

    struct Message {
        virtual std::unique_ptr<Message> clone() const = 0;
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
        std::unique_ptr<Message> clone() const { return std::make_unique<InputMessage>(*this); }
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
        std::unique_ptr<Message> clone() const { return std::make_unique<RenderFieldMessage>(*this); }
    };

    struct RenderFieldPreviewMessage : public Message {
        vec2 size;
        
        RenderFieldPreviewMessage(vec2 size) : size(size) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<RenderFieldPreviewMessage>(*this); }
    };

    struct LogMessage : public Message {
        std::string text;

        LogMessage(std::string text) : text(text) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<LogMessage>(*this); }
    };

    struct ChangeControlMessage : public Message {
        GameControl *new_control;

        ChangeControlMessage(GameControl *new_control) : new_control(new_control) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<ChangeControlMessage>(*this); }
    };
}

#endif
