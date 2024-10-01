#include "states/global.h"
#include "colors.h"
#include "states/global/welcome.h"
#include <GL/gl.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace seabattle {
    GlobalState::GlobalState(sf::RenderWindow &window)
        : window(window),
          substate(new WelcomeState(*this)),
          field(vec2(0, 0))
    {
        if (!font.loadFromFile("assets/font.ttf")) {
            throw std::runtime_error("Failed to load assets/font.ttf");
        }

        message.setFont(font);
        message.setCharacterSize(16);
        message.setPosition(10, window.getSize().y - 16 - 10);
        message.setString("");

        title.setFont(font);
        title.setString("Welcome to Seabattle");
        title.setCharacterSize(16);
        title.setFillColor(sf::Color::White);
        title.setPosition(10, 10);
    }

    void GlobalState::OnKeyDown(sf::Keyboard::Key key)
    {
        if (substate) {
            substate->OnKeyDown(key);
        }
    }

    void GlobalState::Render()
    {
        window.clear(colors::Fog);
        
        field.Render();

        if (substate) {
            substate->Render();
        }

        window.pushGLStates();
        window.draw(title);
        window.draw(message);
        window.popGLStates();
    }
}
