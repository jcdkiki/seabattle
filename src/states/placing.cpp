#include "states/placing.h"

namespace seabattle {
    PlacingGameState::PlacingGameState(Game &game) : GameState(game),
        orientation(Ship::Orientation::HORIZONTAL),
        position(0, 0),
        size(1)
    {}

    void PlacingGameState::OnKeyDown(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::R:
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
