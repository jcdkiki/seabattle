#ifndef SEABATTLE_CONTROL_SETUP_SHIPS_STATE_HPP_
#define SEABATTLE_CONTROL_SETUP_SHIPS_STATE_HPP_

#include "game_state.hpp"
#include <vector>

namespace seabattle {
    class SetupShipsState : public GameState {
        int size;
        int points;
        std::vector<size_t> ship_sizes;

        void showPoints();
        bool canPlace();
        void setupOpponentShips();

    public:
        static constexpr const char *name = "SetupShips";

        SetupShipsState(Game &game);
        void handle(InputMessage message);
        std::string_view getName() const;
    };
}

#endif
