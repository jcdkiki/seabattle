#ifndef SEABATTLE_STATES_GLOBALS_H_
#define SEABATTLE_STATES_GLOBALS_H_

#include <SFML/Window/Keyboard.hpp>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "field.h"
#include "ship_manager.h"

namespace seabattle {
    class GlobalState {
    public:
        class Substate {
        public:
            virtual void onKeyDown(sf::Keyboard::Key) = 0;
            virtual void render() = 0;
            virtual ~Substate() {}
        };

    protected:
        friend class WelcomeState;
        friend class PlacingState;
        friend class BattleState;

        sf::RenderWindow &window;
        sf::Font font;
        sf::Text message;
        sf::Text title;
        Field field;
        ShipManager ship_manager;
        std::unique_ptr<Substate> substate;

    public:
        GlobalState(sf::RenderWindow &window);
        void onKeyDown(sf::Keyboard::Key);
        void render();
    };
}

#endif
