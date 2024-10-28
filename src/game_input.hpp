#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "game.hpp"

namespace seabattle {
    class GameInput {
    public:
        void operator>>(Game &game);
    };
}

#endif // GAME_INPUT_H
