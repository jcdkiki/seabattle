#ifndef SEABATTLE_CONTROL_PLACE_SHIPS_STATE_HPP_
#define SEABATTLE_CONTROL_PLACE_SHIPS_STATE_HPP_

#include "game_state.hpp"
#include "ship_manager.hpp"

namespace seabattle {
    class PlaceShipsState : public GameState {
        vec2 position;
        Ship::Orientation orientation;
        ShipManager::Iterator current_ship;

        bbox2 getCursor();
    public:
        PlaceShipsState(Game &ctx);
        void operator<<(AtomicInputMessage message);
    };
}

#endif
