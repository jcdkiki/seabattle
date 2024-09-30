#ifndef SEABATTLE_GAME_H_
#define SEABATTLE_GAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "states/state.h"
#include "field.h"

namespace seabattle {
    class Game {
        sf::RenderWindow window;
        sf::Font font;
        std::unique_ptr<GameState> state;
        Field field;
    public:
        Game();
        void MainLoop();
        void ChangeState(GameState *new_state);

        inline const sf::Font &GetFont() const { return font; }
        inline sf::RenderWindow& GetWindow() { return window; }
        inline Field GetField() { return field; }
    };
}

#endif
