#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "input_messages.hpp"

namespace seabattle {
    class GameInput {
    public:
        InputMessage *pollMessage();
    };
}

#endif // GAME_INPUT_H
