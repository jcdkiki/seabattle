#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include "game.hpp"

namespace seabattle {
    class GameInput {
    protected:
        Game &game;
    public:
        GameInput(Game &game) : game(game) {}
        void handle();
    };
}

#endif // GAME_INPUT_H
