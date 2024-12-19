#ifndef INPUT_MESSAGE_H
#define INPUT_MESSAGE_H

#include "vec2.hpp"
#include "game.hpp"

namespace seabattle {
    struct InputMessage {
        virtual void execute(Game &game) = 0;
        virtual InputMessage *copy() = 0;
        virtual ~InputMessage() {};
    };

    struct PrimaryActionMessage : public InputMessage {
        InputMessage *copy() { return new PrimaryActionMessage(*this); }
        void execute(Game &game) { game.primaryAction(); }
    };

    struct SecondaryActionMessage : public InputMessage {
        InputMessage *copy() { return new SecondaryActionMessage(*this); }
        void execute(Game &game) { game.secondaryAction(); }
    };

    struct TertiaryActionMessage : public InputMessage {
        InputMessage *copy() { return new TertiaryActionMessage(*this); }
        void execute(Game &game) { game.tertiaryAction(); }
    };

    struct QuitMessage : public InputMessage {
        InputMessage *copy() { return new QuitMessage(*this); }
        void execute(Game &game) { game.quit(); }
    };

    struct SaveMessage : public InputMessage {
        InputMessage *copy() { return new SaveMessage(*this); }
        void execute(Game &game) { game.save(); }
    };

    struct LoadMessage : public InputMessage {
        InputMessage *copy() { return new LoadMessage(*this); }
        void execute(Game &game) { game.load(); }
    };

    struct MoveCursorMessage : public InputMessage {
        vec2 movement;

        MoveCursorMessage(vec2 movement) : movement(movement) {}
        
        InputMessage *copy() { return new MoveCursorMessage(*this); }
        void execute(Game &game) { game.moveCursor(movement); }
    };
}

#endif // INPUT_MESSAGE_H
