#ifndef SEABATTLE_GAME_H_
#define SEABATTLE_GAME_H_

#include "field.hpp"
#include "messaging.hpp"
#include "messages.hpp"
#include "ship_manager.hpp"
#include <string>

namespace seabattle {
    class Game : public MessageTransformer {
    protected:
        enum class State {
            CREATING_FIELD,
            SETUP_SHIPS,
            PLACING_SHIPS,
        };

        State state;
        vec2 choice;

        // SETUP_SHIPS
        std::vector<size_t> ship_sizes;

        // PLACING_SHIPS
        Ship::Orientation orientation;
        ShipManager::Iterator current_ship;

        Field enemy_field;
        Field player_field;
        ShipManager player_ships;
        ShipManager enemy_ships;
        bool is_running;

    public:
        void handleXYChoiceInput(const InputMessage &msg)
        {
            switch (msg.action) {
                case InputMessage::CURSOR_RIGHT: choice.x++; break;
                case InputMessage::CURSOR_LEFT: choice.x--; break;
                case InputMessage::CURSOR_UP: choice.y--; break;
                case InputMessage::CURSOR_DOWN: choice.y++; break;
                default: return;
            }

            pushMessage(new LogMessage("Your choice: " + std::to_string(choice.x) + "x" + std::to_string(choice.y)));
        }

        void handleXChoiceInput(const InputMessage &msg)
        {
            switch (msg.action) {
                case InputMessage::CURSOR_RIGHT: choice.x++; break;
                case InputMessage::CURSOR_LEFT: choice.x--; break;
                default: return;
            }

            pushMessage(new LogMessage("Your choice: " + std::to_string(choice.x)));
        }

        void showShipPlacementInfo()
        {
            pushMessage(new LogMessage("Placing ship of size " + std::to_string(current_ship->getSize())));
        }

        void showSetupShipsInfo()
        {
            pushMessage(new LogMessage("Enter ship size or proceed to placing your ships"));
        }

        void showShipPlacement()
        {
            bbox2 cursor(choice, choice);
            if (current_ship != player_ships.end()) {
                if (orientation == Ship::Orientation::HORIZONTAL)
                    cursor.max += vec2(current_ship->getSize(), 1);
                else
                    cursor.max += vec2(1, current_ship->getSize());
            }

            pushMessage(new RenderFieldMessage(RenderFieldMessage::LEFT, player_field, cursor));
        }

        void handleInputCreatingField(const InputMessage &msg)
        {
            handleXYChoiceInput(msg);

            if (msg.action == InputMessage::PRIMARY_ACTION) {
                try {
                    player_field = Field(choice);
                }
                catch (std::invalid_argument &e) {
                    pushMessage(new LogMessage(e.what()));
                    return;
                }

                choice = vec2(0, 0);
                state = State::SETUP_SHIPS;
                showSetupShipsInfo();
            }
        }

        void handleInputSetupShips(const InputMessage &msg)
        {
            handleXChoiceInput(msg);

            if (msg.action == InputMessage::PRIMARY_ACTION) {
                ship_sizes.push_back(choice.x);
                showSetupShipsInfo();
            }
            else if (msg.action == InputMessage::SECONDARY_ACTION) {
                try {
                    player_ships = ShipManager(ship_sizes.begin(), ship_sizes.end());
                }
                catch (std::invalid_argument &e) {
                    ship_sizes.resize(0);
                    pushMessage(new LogMessage(e.what()));
                    pushMessage(new LogMessage("Try again"));
                    return;
                }

                state = State::PLACING_SHIPS;
                choice = vec2(0, 0);
                ship_sizes.resize(0);
                current_ship = player_ships.begin();
                pushMessage(new LogMessage("Great job, not place your ships!"));
                showShipPlacement();
            }
        }

        void handleInputPlacingShips(const InputMessage &msg)
        {
            handleXYChoiceInput(msg);

            if (msg.action == InputMessage::SECONDARY_ACTION) {
                orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
            }
            else if (msg.action == InputMessage::PRIMARY_ACTION) {
                try {
                    player_field.addShip(*current_ship, choice, orientation, true);
                    current_ship++;
                }
                catch (std::invalid_argument &e) {
                    pushMessage(new LogMessage(e.what()));
                }

                if (current_ship == player_ships.end()) {
                    pushMessage(new LogMessage("You rooock duuude!"));
                    state = State::CREATING_FIELD;
                    return;
                }
            }

            showShipPlacement();
        }

        void handleInput(const InputMessage &msg)
        {
            if (msg.action == InputMessage::BACK) {
                is_running = false;
            }

            switch (state) {
                case State::CREATING_FIELD: handleInputCreatingField(msg); return;
                case State::SETUP_SHIPS: handleInputSetupShips(msg); return;
                case State::PLACING_SHIPS: handleInputPlacingShips(msg); return;
            }
        }

        bool isRunning()
        {
            return is_running;
        }

        Game() : is_running(true), player_field(vec2(0, 0)), enemy_field(vec2(0, 0))
        {
            registerHandler<InputMessage>((HandlerMethod)&Game::handleInput);
        }
    };
}

#endif
