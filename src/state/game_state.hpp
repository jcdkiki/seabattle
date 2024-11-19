#ifndef SEABATTLE_CONTROL_GAME_STATE_HPP_
#define SEABATTLE_CONTROL_GAME_STATE_HPP_

#include "input_messages.hpp"
#include "vec2.hpp"

#include "player.hpp"

namespace seabattle {
    class Game;

    class GameState {
    protected:
        Game &ctx;
        Player &player();
        Player &opponent();

        bool handleXYInput(vec2 &vec, const AtomicInputMessage msg);
        bool handleXInput(int &x, const AtomicInputMessage msg);

    public:
        GameState(Game &ctx) : ctx(ctx) {}
        virtual ~GameState() {};
    
        virtual void operator<<(AtomicInputMessage message) = 0;
    };
}

#endif
