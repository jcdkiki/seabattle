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

        void load(std::istream &is);
        void save(std::ostream &os);

    public:
        static constexpr const char *name = "PlaceShips";

        PlaceShipsState(Game &game);
        void handle(InputMessage message);
        std::string_view getName() const;

        friend std::ostream &operator<<(std::ostream &os, PlaceShipsState &state);
        friend std::istream &operator>>(std::istream &is, PlaceShipsState &state);
    };
}

#endif
