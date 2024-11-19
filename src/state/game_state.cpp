#include "game_state.hpp"
#include "game.hpp"

namespace seabattle {
    Player &GameState::player() { return ctx.player; }
    Player &GameState::opponent() { return ctx.opponent; }

    bool GameState::handleXYInput(vec2 &vec, AtomicInputMessage msg)
    {
        switch (msg.kind) {
            case AtomicInputMessage::CURSOR_RIGHT: vec.x++; break;
            case AtomicInputMessage::CURSOR_LEFT: vec.x--; break;
            case AtomicInputMessage::CURSOR_UP: vec.y--; break;
            case AtomicInputMessage::CURSOR_DOWN: vec.y++; break;
            default: return false;
        }

        return true;
    }

    bool GameState::handleXInput(int &x, AtomicInputMessage msg)
    {
        switch (msg.kind) {
            case AtomicInputMessage::CURSOR_RIGHT: x++; break;
            case AtomicInputMessage::CURSOR_LEFT: x--; break;
            default: return false;
        }

        return true;
    }
};
