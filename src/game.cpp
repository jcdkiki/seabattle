#include "game.hpp"
#include "input/message.hpp"
#include "player.hpp"
#include "state_registry.hpp"
#include "states/setup_field_state.hpp"
#include <fstream>

#include <istream>
#include <ostream>

namespace seabattle {
    Game::Game(GameRenderer &renderer) :
        renderer(renderer), is_running(true)
    {
        state = new SetupFieldState(*this);
        is_state_new = true;
    }

    void Game::save()
    {
        std::ofstream ofs("data/game.sav");
        ofs << *this;
        renderer.handle("Game saved!");
    }

    void Game::load()
    {
        std::ifstream ifs("data/game.sav");
        if (!ifs.is_open()) {
            renderer.handle("Failed to load gamesave");
            return;
        }
        ifs >> *this;
        renderer.handle("Game loaded!");
    }

    void Game::handle(InputMessage message)
    {
        switch (message.kind) {
            case InputMessage::QUIT:
                this->stop();
                return;
            
            case InputMessage::SAVE:
                this->save();
                return;
            
            case InputMessage::LOAD:
                this->load();
                return;
            
            default:
                state->handle(message);
                is_state_new = false;
        }
    }

    void Game::updateState(GameState *new_state)
    {
        if (is_state_new)
            return;

        delete state;
        state = new_state;
        is_state_new = true;
    }

    Game::~Game()
    {
        delete state;
    }

    std::ostream &operator<<(std::ostream &os, Game &game)
    {
        os << game.player << '\n';
        os << game.opponent << '\n';
        os << game.ai << '\n';
        os << game.state->getName() << '\n';
        os << *game.state;
        return os;
    }

    std::istream &operator>>(std::istream &is, Game &game)
    {
        is >> game.player;
        is >> game.opponent;
        is >> game.ai;

        game.ai.setField(&game.player.field);

        std::string state_name;
        is >> state_name;

        GameState *new_state = StateRegistry::self().find(state_name)->second.generator(game);
        is >> *game.state;
        game.updateState(new_state);

        return is;
    }
}
