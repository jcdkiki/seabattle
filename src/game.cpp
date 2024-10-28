#include "game.hpp"
#include "input_messages.hpp"
#include "state/game_state.hpp"
#include "state/setup_field_state.hpp"

namespace seabattle {
    Game::Game(GameRenderer &renderer) : MessagePipe(renderer),
        is_running(true), state(new SetupFieldState(*this)) 
    {}

    void Game::operator<<(AtomicInputMessage message)
    {
        if (message.kind == AtomicInputMessage::QUIT) {
            this->stop();
            return;
        }

        *state << message;
    }

    void Game::changeState(GameState *new_state)
    {
        delete state;
        state = new_state;
    }

    Game::~Game()
    {
        delete state;
    }
}
