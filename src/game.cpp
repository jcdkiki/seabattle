#include "game.hpp"
#include "player.hpp"
#include "state_registry.hpp"
#include "states/setup_field_state.hpp"
#include <fstream>

#include <istream>
#include <ostream>

namespace seabattle {
    Game::Game() : is_running(true), renderer(nullptr)
    {
        state = new SetupFieldState(*this);
    }

    void Game::load()
    {
        std::ifstream ifs("data/game.sav");
        if (!ifs.is_open()) {
            render("Failed to load gamesave");
            return;
        }
        ifs >> *this;
        render("Game loaded!");
    }

    void Game::save()
    {
        std::ofstream ofs("data/game.sav");
        ofs << *this;
        render("Game saved!");
    }

    void Game::quit()
    {
        is_running = false;
    }

    void Game::updateState(GameState *new_state)
    {
        delete state;
        state = new_state;
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
        delete game.state;
        game.state = new_state;
        
        return is;
    }
}
