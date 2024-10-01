#ifndef SEABATTLE_STATES_BATTLE_H_
#define SEABATTLE_STATES_BATTLE_H_

#include "states/global.h"
#include <SFML/Graphics/Text.hpp>

namespace seabattle {
    class BattleState : public GlobalState::Substate {
        GlobalState &global;
        vec2 cursor;
    public:
        BattleState(GlobalState &global);
        virtual void OnKeyDown(sf::Keyboard::Key key) override;
        virtual void Render() override;
        virtual ~BattleState() = default;
    };
}

#endif
