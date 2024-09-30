#ifndef SEABATTLE_STATES_PLACING_H_
#define SEABATTLE_STATES_PLACING_H_

#include "game.h"
#include "ship.h"

namespace seabattle {
    class PlacingGameState : public GameState {
        Ship::Orientation orientation;
        vec2 position;
        size_t size;
    public:
        PlacingGameState(Game &game);
        virtual void OnKeyDown(sf::Keyboard::Key key) override;
        virtual void Render() override;
        virtual ~PlacingGameState() = default;
    };
}

#endif
