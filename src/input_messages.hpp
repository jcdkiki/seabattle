#ifndef INPUT_MESSAGE_H
#define INPUT_MESSAGE_H

namespace seabattle {
    struct AtomicInputMessage {
        enum Kind {
            INVALID = -1,
            PRIMARY_ACTION,
            SECONDARY_ACTION,
            CURSOR_LEFT,
            CURSOR_RIGHT,
            CURSOR_UP,
            CURSOR_DOWN,
            QUIT
        };

        Kind kind;
        AtomicInputMessage(Kind kind) : kind(kind) {}

        ~AtomicInputMessage() {}
    };
}

#endif // INPUT_MESSAGE_H
