#ifndef SEABATTLE_MESSAGING_GAME_MESSAGES_HPP_
#define SEABATTLE_MESSAGING_GAME_MESSAGES_HPP_

#include "message.hpp"

namespace seabattle {
    class GameControl;

    struct ChangeControlMessage : public Message {
        GameControl *new_control;

        ChangeControlMessage(GameControl *new_control) : new_control(new_control) {}
        std::unique_ptr<Message> clone() const { return std::make_unique<ChangeControlMessage>(*this); }
    };
}

#endif
