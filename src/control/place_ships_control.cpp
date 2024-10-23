#include "place_ships_control.hpp"
#include "fight_control.hpp"

namespace seabattle {
    void PlaceShipsControl::showShipPlacement()
    {
        bbox2 cursor(position, position);
        if (current_ship != state.player.ships.end()) {
            if (orientation == Ship::Orientation::HORIZONTAL)
                cursor.max += vec2(current_ship->getSize(), 1);
            else
                cursor.max += vec2(1, current_ship->getSize());
        }

        emplace<RenderFieldMessage>(state.player.field, cursor);
    }

    PlaceShipsControl::PlaceShipsControl(GameState &state) : GameControl(state)
    {
        emplace<LogMessage>("Great job, now place your ships");
        current_ship = state.player.ships.begin();

        showShipPlacement();
    }

    void PlaceShipsControl::handleInput(std::unique_ptr<const InputMessage> msg)
    {
        if (msg->action == InputMessage::SECONDARY_ACTION) {
            orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
        }
        else if (msg->action == InputMessage::PRIMARY_ACTION) {
            try {
                state.player.field.addShip(*current_ship, position, orientation, true);
                current_ship++;
            }
            catch (IllegalShipPositionException &e) {
                emplace<LogMessage>(e.what());
            }

            if (current_ship == state.player.ships.end()) {
                emplace<ChangeControlMessage>(new FightControl(state));
            }
        }
        else if (handleXYInput(position, *msg)) {
            emplace<RenderCursorMessage>(position);
        }

        showShipPlacement();
    }
}
