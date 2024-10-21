#ifndef SEABATTLE_MESSAGING_INPUT_MESSAGES_HPP_
#define SEABATTLE_MESSAGING_INPUT_MESSAGES_HPP_

#include "message.hpp"

namespace seabattle {
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
};

#endif
