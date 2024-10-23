#include "setup_ships_control.hpp"
#include "place_ships_control.hpp"

namespace seabattle {
    SetupShipsControl::SetupShipsControl(GameState &state) : GameControl(state), size(0)
    {
        emplace<LogMessage>("Good job, now select ship sizes!");
    }

    void SetupShipsControl::handleInput(std::unique_ptr<const InputMessage> msg)
    {
        if (msg->action == InputMessage::PRIMARY_ACTION) {
            if (size <= 0 || size > Ship::MAX_SIZE) {
                emplace<LogMessage>("Invalid ship size. Try again");
            }
            else {
                ship_sizes.push_back(size);
                emplace<LogMessage>("Added ship. Now create another one or proceed to the next stage");
            }
        }
        else if (msg->action == InputMessage::SECONDARY_ACTION) {
            try {
                state.player.ships = ShipManager(ship_sizes.begin(), ship_sizes.end());
                emplace<ChangeControlMessage>(new PlaceShipsControl(state));
            }
            catch (std::invalid_argument &e) {
                emplace<LogMessage>(std::string("Error: ") + e.what() + " | Try again.");
                emplace<ChangeControlMessage>(new SetupShipsControl(state));
            }
        }
        else handleXInput(size, *msg);
    }
}
