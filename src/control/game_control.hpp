#ifndef SEABATTLE_CONTROL_GAME_CONTROL_HPP_
#define SEABATTLE_CONTROL_GAME_CONTROL_HPP_

#include "game_state.hpp"
#include "messaging/input_messages.hpp"
#include "messaging/render_messages.hpp"

namespace seabattle {
    class GameControl : public MessageGenerator {
    protected:
        GameState &state;

        bool handleXYInput(vec2 &vec, const InputMessage &msg);
        bool handleXInput(int &x, const InputMessage &msg);
        
    public:
        GameControl(GameState &state) : state(state) {}
        virtual ~GameControl() {};
        virtual void handleInput(std::unique_ptr<const InputMessage> msg) = 0;
    };
}

#endif
