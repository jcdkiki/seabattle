#ifndef SEABATTLE_GAME_H_
#define SEABATTLE_GAME_H_

#include "messaging/message_pipe.hpp"
#include "control/setup_field_control.hpp"

namespace seabattle {
    class Game : public MessagePipe {
    protected:
        GameState state;
        std::unique_ptr<GameControl> control;
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
            control.reset(msg->new_control);
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
    };
}

#endif
