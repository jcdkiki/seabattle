#include "ai_action_state.hpp"
#include "ai_controller.hpp"
#include "game.hpp"
#include "player_action_state.hpp"
#include "setup_ai_state.hpp"
#include "setup_field_state.hpp"
#include "state_registration.hpp"

namespace seabattle {
    AIActionState::AIActionState(Game &game) : GameState(game)
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();
        AIController &ai = game.getAIController();

        if (opponent.ships.countActiveShips() == 0) { // WIN!
            game.render("BIG MAN. BIG W");
            game.updateState(new SetupAIState(game));
            return;
        }
        if (player.ships.countActiveShips() == 0) { // LOSE!
            game.render("You failed!!! *boo-womp*");
            game.updateState(new SetupFieldState(game));
            return;
        }

        opponent.cursor = ai.choose();
        auto result = opponent.attack(player);
        ai.see(result);

        game.render("Your opponent attacks!!! Press any key to continue");
        game.render(player.field);
        game.render(bbox2(opponent.cursor, opponent.cursor + vec2(1, 1)));
    }

    void AIActionState::handle(InputMessage message)
    {
        game.updateState(new PlayerActionState(game));
    }

    static StateRegistration<AIActionState> registration;
    std::string_view AIActionState::getName() const { return name; }
}
