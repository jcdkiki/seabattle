#ifndef SEABATTLE_GAME_H_
#define SEABATTLE_GAME_H_

#include "messaging.hpp"
#include "messages.hpp"
#include <memory>
#include <stdexcept>
#include <string>

#include "human_player.hpp"
#include "player.hpp"

namespace seabattle {
    struct GameState {
        HumanPlayer player;
        Player opponent;

        GameState() : player(opponent) {}
    };
    
    class GameControl : public MessageGenerator {
    protected:
        GameState &state;

        bool handleXYInput(vec2 &vec, const InputMessage &msg)
        {
            switch (msg.action) {
                case InputMessage::CURSOR_RIGHT: vec.x++; break;
                case InputMessage::CURSOR_LEFT: vec.x--; break;
                case InputMessage::CURSOR_UP: vec.y--; break;
                case InputMessage::CURSOR_DOWN: vec.y++; break;
                default: return false;
            }

            emplace<LogMessage>("Your input: " + std::to_string(vec.x) + "x" + std::to_string(vec.y));
            return true;
        }

        bool handleXInput(int &x, const InputMessage &msg)
        {
            switch (msg.action) {
                case InputMessage::CURSOR_RIGHT: x++; break;
                case InputMessage::CURSOR_LEFT: x--; break;
                default: return false;
            }

            emplace<LogMessage>("Your choice: " + std::to_string(x));
            return true;
        }

    public:
        GameControl(GameState &state) : state(state) {}
        virtual ~GameControl() {};
        virtual void handleInput(std::unique_ptr<const InputMessage> msg) = 0;
    };

    class FightControl : public GameControl {
    public:
        FightControl(GameState &state) : GameControl(state)
        {
            state.player.field.coverInFog();
            emplace<LogMessage>("Great job! Now it's time to FIGHT!!!!");

            bbox2 cursor(state.player.cursor, state.player.cursor + vec2(1, 1));
            emplace<RenderFieldMessage>(RenderFieldMessage::LEFT, state.player.field, cursor);
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
        {
            if (msg->action == InputMessage::PRIMARY_ACTION) {
                try {
                    state.player.attack(state.player);
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                }

                // AI attack code will be here
            }
            else if (msg->action == InputMessage::SECONDARY_ACTION) {
                try {
                    state.player.useAbility(state.player);
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                }
            }
            else handleXYInput(state.player.cursor, *msg);

            bbox2 cursor(state.player.cursor, state.player.cursor + vec2(1, 1));
            emplace<RenderFieldMessage>(RenderFieldMessage::LEFT, state.player.field, cursor);
        }
    };

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

    class SetupShipsControl : public GameControl {
        int size;
        std::vector<size_t> ship_sizes;
    public:
        SetupShipsControl(GameState &state) : GameControl(state), size(0)
        {
            emplace<LogMessage>("Good job, now select ship sizes!");
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
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
    };

    class SetupFieldControl : public GameControl {
        vec2 size;
    public:
        SetupFieldControl(GameState &state) : GameControl(state)
        {
            emplace<LogMessage>("Welcome to seabattle. Select field size");
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
        {
            if (handleXYInput(size, *msg)) {
                emplace<RenderFieldPreviewMessage>(size);
                return;
            }

            if (msg->action == InputMessage::PRIMARY_ACTION) {
                try {
                    state.player.field = Field(size);
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                    return;
                }

                emplace<ChangeControlMessage>(new SetupShipsControl(state));
            }
        }
    };

    class Game : public MessagePipe {
    protected:
        GameState state;
        GameControl *control;
        bool is_running;

    public:
        bool isRunning()
        {
            return is_running;
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
        {
            if (msg->action == InputMessage::BACK) {
                is_running = false;
                return;
            }

            control->handleInput(std::move(msg));

            while (!control->empty()) {
                this->handleMessage(std::move(control->pop()));
            }
        }

        void handleChangeControl(std::unique_ptr<const ChangeControlMessage> msg)
        {
            delete control;
            control = msg->new_control;
        }

        void update(MessageGenerator &input, MessageReciever &output)
        {
            input.update();
            while (!input.empty()) {
                this->handleMessage(std::move(input.pop()));
            }

            while (!state.player.empty()) {
                this->handleMessage(std::move(state.player.pop()));
            }

            while (!this->empty()) {
                output.handleMessage(std::move(this->pop()));
            }
            output.update();
        }

        Game() : is_running(true), control(new SetupFieldControl(state))
        {
            registerHandler<InputMessage>((HandlerMethod)&Game::handleInput);
            registerHandler<ChangeControlMessage>((HandlerMethod)&Game::handleChangeControl);
        }
        
        ~Game()
        {
            delete control;
        }
    };
}

#endif
