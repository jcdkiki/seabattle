#ifndef SEABATTLE_STATES_WELCOME_H_
#define SEABATTLE_STATES_WELCOME_H_

#include <SFML/Graphics/Text.hpp>

#include "states/global.hpp"
#include "vec2.hpp"

namespace seabattle {
    class WelcomeState : public GlobalState::Substate {
        GlobalState &global;
        vec2 field_size;
        bool is_width_done;

        sf::Text field_size_text;
        
    public:
        WelcomeState(GlobalState &global);
        virtual void onKeyDown(sf::Keyboard::Key key) override;
        virtual void render() override;
        virtual ~WelcomeState() = default;
    };
}

#endif
