#include "game.h"

#include <SFML/OpenGL.hpp>
#include "states/placing.h"

namespace seabattle {
    Game::Game()
        : window(sf::VideoMode(640, 480), "Seabattle", sf::Style::Titlebar),
          state(new PlacingGameState(*this)),
          field(vec2(0, 0))
    {
        if (!font.loadFromFile("assets/font.ttf")) {
            throw std::runtime_error("Failed to load assets/font.ttf");
        }

        glViewport(0, 0, 640, 480);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 640, 480, 0.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
    }

    void Game::MainLoop()
    {
        sf::Text text;
        text.setFont(font);

        text.setString("Welcome to Seabattle");
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(10.f, 10.f));

        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        state->OnKeyDown(event.key.code);
                        break;
                    default:
                        break;
                }
            }

            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            window.draw(text);
            window.display();
        }
    };

    void Game::ChangeState(GameState *new_state)
    {
        state = std::unique_ptr<GameState>(new_state);
    }
}
