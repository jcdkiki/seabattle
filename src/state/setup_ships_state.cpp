#include "setup_ships_state.hpp"
#include "place_ships_state.hpp"
#include "game.hpp"

namespace seabattle {
    SetupShipsState::SetupShipsState(Game &ctx) : GameState(ctx), size(0)
    {
        ctx << "Select ship sizes!";
    }

    void SetupShipsState::operator<<(AtomicInputMessage message)
    {
        if (message.kind == AtomicInputMessage::PRIMARY_ACTION) {
            if (size <= 0 || size > Ship::MAX_SIZE) {
                ctx << "Invalid ship size. Try again";
            }
            else {
                ship_sizes.push_back(size);
                ctx << "Added ship. Now create another one or proceed to the next stage";
            }
        }
        else if (message.kind == AtomicInputMessage::SECONDARY_ACTION) {
            try {
                player().ships = ShipManager(ship_sizes.begin(), ship_sizes.end());
                ctx.changeState(new PlaceShipsState(ctx));
            }
            catch (std::invalid_argument &e) {
                ctx << (std::string("Error: ") + e.what() + " | Try again.");
                ctx.changeState(new SetupShipsState(ctx));
            }
        }
        else if (handleXInput(size, message)) {
            ctx << ("Ship size: " + std::to_string(size)); 
        }
    }
}
