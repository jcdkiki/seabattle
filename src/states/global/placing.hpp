#ifndef SEABATTLE_STATES_PLACING_H_
#define SEABATTLE_STATES_PLACING_H_

#include "ship_manager.hpp"
#include "states/global.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace seabattle {
    class PlacingState : public GlobalState::Substate {
        GlobalState &global;
        ShipManager::Iterator current_ship;
        Ship::Orientation orientation;
        vec2 position;

        sf::Text ship_count_text;
    public:

        PlacingState(GlobalState &global);
        virtual void onKeyDown(sf::Keyboard::Key key) override;
        virtual void render() override;
        virtual ~PlacingState() override = default;
    };
}

#endif