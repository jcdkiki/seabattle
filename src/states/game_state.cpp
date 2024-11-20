#include "game_state.hpp"

namespace seabattle {
    bool GameState::handleXYInput(vec2 &vec, InputMessage msg)
    {
        switch (msg.kind) {
            case InputMessage::CURSOR_RIGHT: vec.x++; break;
            case InputMessage::CURSOR_LEFT: vec.x--; break;
            case InputMessage::CURSOR_UP: vec.y--; break;
            case InputMessage::CURSOR_DOWN: vec.y++; break;
            default: return false;
        }

        return true;
    }

    bool GameState::handleXInput(int &x, InputMessage msg)
    {
        switch (msg.kind) {
            case InputMessage::CURSOR_RIGHT: x++; break;
            case InputMessage::CURSOR_LEFT: x--; break;
            default: return false;
        }

        return true;
    }

    void GameState::save(std::ostream &os) {}
    void GameState::load(std::istream &is) {}
};
