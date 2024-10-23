#include "game_control.hpp"

namespace seabattle {
    bool GameControl::handleXYInput(vec2 &vec, const InputMessage &msg)
    {
        switch (msg.action) {
            case InputMessage::CURSOR_RIGHT: vec.x++; break;
            case InputMessage::CURSOR_LEFT: vec.x--; break;
            case InputMessage::CURSOR_UP: vec.y--; break;
            case InputMessage::CURSOR_DOWN: vec.y++; break;
            default: return false;
        }

        return true;
    }

    bool GameControl::handleXInput(int &x, const InputMessage &msg)
    {
        switch (msg.action) {
            case InputMessage::CURSOR_RIGHT: x++; break;
            case InputMessage::CURSOR_LEFT: x--; break;
            default: return false;
        }

        emplace<LogMessage>("Your choice: " + std::to_string(x));
        return true;
    }
};
