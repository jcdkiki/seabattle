#ifndef INPUT_MESSAGE_H
#define INPUT_MESSAGE_H

namespace seabattle {
    struct InputMessage {
        enum Kind {
            INVALID = -1,
            PRIMARY_ACTION,
            SECONDARY_ACTION,
            TERTIARY_ACTION,
            CURSOR_LEFT,
            CURSOR_RIGHT,
            CURSOR_UP,
            CURSOR_DOWN,
            QUIT,
            SAVE,
            LOAD,
            TOTAL_MESSAGES
        };

        Kind kind;
        InputMessage(Kind kind = INVALID) : kind(kind) {}

        ~InputMessage() {}
    };
}

#endif // INPUT_MESSAGE_H
