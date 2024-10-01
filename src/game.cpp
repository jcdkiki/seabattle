#include "game.h"

#include <GL/gl.h>
#include <SFML/Graphics/RenderWindow.hpp> 
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace seabattle {
    Game::Game()
        : window(sf::VideoMode(640, 480), "Seabattle", sf::Style::Titlebar, sf::ContextSettings(0, 0, 0, 4, 5)),
          state(window)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 640, 480, 0, 0, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void Game::MainLoop()
    {
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        state.OnKeyDown(event.key.code);
                        break;
                    default:
                        break;
                }
            }

            state.Render();
            
            window.display();
        }
    };
}
