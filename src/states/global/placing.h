#ifndef SEABATTLE_STATES_PLACING_H_
#define SEABATTLE_STATES_PLACING_H_

#include "states/global.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace seabattle {
    class PlacingState : public GlobalState::Substate {
        GlobalState &global;
        Ship::Orientation orientation;
        vec2 position;
        int size;

        sf::Text ship_count_text;
    public:

        PlacingState(GlobalState &global);
        virtual void onKeyDown(sf::Keyboard::Key key) override;
        virtual void render() override;
        virtual ~PlacingState() override = default;
    };
}

#endif
