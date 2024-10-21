#ifndef SEABATTLE_GAME_STATE_HPP_
#define SEABATTLE_GAME_STATE_HPP_

#include "human_player.hpp"
#include "player.hpp"

namespace seabattle {
    struct GameState {
        HumanPlayer player;
        Player opponent;

        GameState() : player(opponent) {}
    };
}

#endif
