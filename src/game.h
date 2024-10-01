#ifndef SEABATTLE_GAME_H_
#define SEABATTLE_GAME_H_

#include <SFML/Graphics/RenderWindow.hpp> 
#include "states/global.h"

namespace seabattle {
    class Game {
        sf::RenderWindow window;
        GlobalState state;
    public:
        Game();
        void mainLoop();
    };
}

#endif
