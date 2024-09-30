#ifndef SEABATTLE_STATES_WELCOME_H_
#define SEABATTLE_STATES_WELCOME_H_

#include "game.h"
#include "vec2.h"

namespace seabattle {
    class WelcomeGameState : public GameState {
        vec2 field_size;
        bool is_width_done;

        sf::Text help_text;
        sf::Text field_size_text;

        void CreateField();

    public:
        WelcomeGameState(Game &game);
        virtual void OnKeyDown(sf::Keyboard::Key key) override;
        virtual void Render() override;
        virtual ~WelcomeGameState() = default;
    };
}

#endif
