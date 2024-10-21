#ifndef SEABATTLE_CONTROL_GAME_CONTROL_HPP_
#define SEABATTLE_CONTROL_GAME_CONTROL_HPP_

#include "game_state.hpp"
#include "messaging/input_messages.hpp"

namespace seabattle {
    class GameControl : public MessageGenerator {
    protected:
        GameState &state;

        bool handleXYInput(vec2 &vec, const InputMessage &msg)
        {
            switch (msg.action) {
                case InputMessage::CURSOR_RIGHT: vec.x++; break;
                case InputMessage::CURSOR_LEFT: vec.x--; break;
                case InputMessage::CURSOR_UP: vec.y--; break;
                case InputMessage::CURSOR_DOWN: vec.y++; break;
                default: return false;
            }

            emplace<LogMessage>("Your input: " + std::to_string(vec.x) + "x" + std::to_string(vec.y));
            return true;
        }

        bool handleXInput(int &x, const InputMessage &msg)
        {
            switch (msg.action) {
                case InputMessage::CURSOR_RIGHT: x++; break;
                case InputMessage::CURSOR_LEFT: x--; break;
                default: return false;
            }

            emplace<LogMessage>("Your choice: " + std::to_string(x));
            return true;
        }

    public:
        GameControl(GameState &state) : state(state) {}
        virtual ~GameControl() {};
        virtual void handleInput(std::unique_ptr<const InputMessage> msg) = 0;
    };
}

#endif
