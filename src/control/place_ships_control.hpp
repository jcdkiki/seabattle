#ifndef SEABATTLE_CONTROL_PLACE_SHIPS_CONTROL_HPP_
#define SEABATTLE_CONTROL_PLACE_SHIPS_CONTROL_HPP_

#include "game_control.hpp"
#include "fight_control.hpp"
#include "messaging/game_messages.hpp"

namespace seabattle {
    class PlaceShipsControl : public GameControl {
        vec2 position;
        Ship::Orientation orientation;
        ShipManager::Iterator current_ship;

        void showShipPlacement()
        {
            bbox2 cursor(position, position);
            if (current_ship != state.player.ships.end()) {
                if (orientation == Ship::Orientation::HORIZONTAL)
                    cursor.max += vec2(current_ship->getSize(), 1);
                else
                    cursor.max += vec2(1, current_ship->getSize());
            }

            emplace<RenderFieldMessage>(RenderFieldMessage::LEFT, state.player.field, cursor);
        }

    public:
        PlaceShipsControl(GameState &state) : GameControl(state)
        {
            emplace<LogMessage>("Great job, now place your ships");
            current_ship = state.player.ships.begin();

            showShipPlacement();
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
        {
            if (msg->action == InputMessage::SECONDARY_ACTION) {
                orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
            }
            else if (msg->action == InputMessage::PRIMARY_ACTION) {
                try {
                    state.player.field.addShip(*current_ship, position, orientation, true);
                    current_ship++;
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                }

                if (current_ship == state.player.ships.end()) {
                    emplace<ChangeControlMessage>(new FightControl(state));
                }
            }
            else handleXYInput(position, *msg);

            showShipPlacement();
        }
    };
}

#endif
