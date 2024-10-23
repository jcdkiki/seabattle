#ifndef SEABATTLE_CONTROL_PLACE_SHIPS_CONTROL_HPP_
#define SEABATTLE_CONTROL_PLACE_SHIPS_CONTROL_HPP_

#include "game_control.hpp"
#include "messaging/game_messages.hpp"

namespace seabattle {
    class PlaceShipsControl : public GameControl {
        vec2 position;
        Ship::Orientation orientation;
        ShipManager::Iterator current_ship;

        void showShipPlacement();
    public:
        PlaceShipsControl(GameState &state);
        void handleInput(std::unique_ptr<const InputMessage> msg);
    };
}

#endif
