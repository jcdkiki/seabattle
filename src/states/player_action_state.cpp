#include "player_action_state.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "setup_field_state.hpp"
#include "states/press_key_state.hpp"
#include "states/setup_ai_state.hpp"

namespace seabattle {
    PlayerActionState::PlayerActionState(Game &game) : GameState(game)
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

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

        game.render("FIGHT!!!!");

        bbox2 cursor(player.cursor, player.cursor + vec2(1, 1));
        game.render(cursor);
        game.render(opponent.field);
    }

    void PlayerActionState::primaryAction()
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        try {
            Field::AttackResult res = player.attack(opponent);
            game.render(opponent.field);

            if (res == Field::AttackResult::SHIP_DESTROYED) {
                game.render(std::string("New ability: ") + player.abilities.top().name.data());
            }

            game.updateState(new PressKeyState(game));
        }
        catch (SeabattleException &e) {
            game.render(e.what());
        }
    }
    
    void PlayerActionState::secondaryAction()
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        try {
            std::shared_ptr<Ability> ability = player.useAbility(opponent);
            game.render(ability);
            game.render(opponent.field);
        }
        catch (SeabattleException &e) {
            game.render(e.what());
        }
    }
    
    void PlayerActionState::tertiaryAction()
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        try {
            opponent.field.mark(player.cursor);
            game.render(opponent.field);
        }
        catch (SeabattleException &e) {
            game.render(e.what());
        }
    }
    
    void PlayerActionState::moveCursor(vec2 amount)
    {
        Player &player = game.getPlayer();
        player.cursor += amount;
        game.render(bbox2(player.cursor, player.cursor + vec2(1, 1)));
    }

    static StateRegistration<PlayerActionState> registration;
    std::string_view PlayerActionState::getName() const { return name; }
}
