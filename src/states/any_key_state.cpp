#include "any_key_state.hpp"
#include "ai_action_state.hpp"
#include "game.hpp"

namespace seabattle {
    AnyKeyState::AnyKeyState(Game &game) : GameState(game)
    {
        game.render("Press any key to continue");
    }

    void AnyKeyState::handle(InputMessage message)
    {
        game.updateState(new AIActionState(game));
    }

    static StateRegistration<AnyKeyState> registration;
    std::string_view AnyKeyState::getName() const { return name; }
}
