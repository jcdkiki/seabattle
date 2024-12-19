#include "press_key_state.hpp"
#include "ai_action_state.hpp"
#include "game.hpp"

namespace seabattle {
    PressKeyState::PressKeyState(Game &game) : GameState(game)
    {
        game.render("Press primary key to continue");
    }

    void PressKeyState::primaryAction()
    {
        game.updateState(new AIActionState(game));
    }

    static StateRegistration<PressKeyState> registration;
    std::string_view PressKeyState::getName() const { return name; }
}
