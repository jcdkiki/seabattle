#include "states/welcome.h"
#include <SFML/Window/Keyboard.hpp>

#include "states/placing.h"

namespace seabattle {
    WelcomeGameState::WelcomeGameState(Game &game) : GameState(game),
        field_size(0, 0),
        is_width_done(false)
    {}

    void WelcomeGameState::CreateField()
    {
        game.GetField()
    }

    void WelcomeGameState::OnKeyDown(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::Enter:
                game.ChangeState(new PlacingGameState(game));
                break;

                orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
                break;
            case sf::Keyboard::E:
                size++;
                break;
            case sf::Keyboard::Q:
                size--;
                break;
            default:
                break;
        }
    }

    void PlacingGameState::Render()
    {

    }
}
