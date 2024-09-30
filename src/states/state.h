#ifndef SEABATTLE_STATES_STATE_H_
#define SEABATTLE_STATES_STATE_H_

#include <SFML/Window/Keyboard.hpp>

namespace seabattle {
    class Game;

    class GameState {
    protected:
        Game &game;
    public:
        GameState(Game &game) : game(game) {}
        virtual void OnKeyDown(sf::Keyboard::Key) = 0;
        virtual void Render() = 0;
        virtual ~GameState() {};
    };
}

#endif
