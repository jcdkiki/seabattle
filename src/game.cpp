#include "game.hpp"
#include "control/setup_field_control.hpp"

namespace seabattle {
    void Game::handleInput(std::unique_ptr<const InputMessage> msg)
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

    void Game::handleChangeControl(std::unique_ptr<const ChangeControlMessage> msg)
    {
        control.reset(msg->new_control);
    }

    void Game::update(MessageGenerator &input, MessageReciever &output)
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

    Game::Game() : is_running(true), control(new SetupFieldControl(state))
    {
        registerHandler<InputMessage>((HandlerMethod)&Game::handleInput);
        registerHandler<ChangeControlMessage>((HandlerMethod)&Game::handleChangeControl);
    }
}
