#include "place_ships_state.hpp"
#include "fight_state.hpp"
#include "game.hpp"

namespace seabattle {
    bbox2 PlaceShipsState::getCursor()
    {
        bbox2 cursor(position, position);
        if (current_ship != player().ships.end()) {
            if (orientation == Ship::Orientation::HORIZONTAL)
                cursor.max += vec2(current_ship->getSize(), 1);
            else
                cursor.max += vec2(1, current_ship->getSize());
        }

        return cursor;
    }

    PlaceShipsState::PlaceShipsState(Game &ctx) : GameState(ctx)
    {
        ctx << "Great job, now place your ships";
        current_ship = player().ships.begin();

        ctx << this->getCursor();
        ctx << player().field;
    }

    void PlaceShipsState::operator<<(AtomicInputMessage message)
    {
        if (message.kind == AtomicInputMessage::SECONDARY_ACTION) {
            orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
        }
        else if (message.kind == AtomicInputMessage::PRIMARY_ACTION) {
            try {
                player().field.addShip(*current_ship, position, orientation, true);
                current_ship++;
            }
            catch (IllegalShipPositionException &e) {
                ctx << e.what();
            }

            if (current_ship == player().ships.end()) {
                ctx.changeState(new FightState(ctx));
                return;
            }
        }
        else handleXYInput(position, message);

        ctx << this->getCursor();
        ctx << player().field;
    }
}
