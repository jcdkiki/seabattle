#include "player_action_state.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "input/message.hpp"
#include "setup_field_state.hpp"
#include "states/any_key_state.hpp"
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

    void PlayerActionState::attack()
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        Field::AttackResult res = player.attack(opponent);
        game.render(opponent.field);

        if (res == Field::AttackResult::SHIP_DESTROYED) {
            game.render(std::string("New ability: ") + player.abilities.top().name.data());
        }

        game.updateState(new AnyKeyState(game));
    }
    
    void PlayerActionState::useAbility()
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        std::shared_ptr<Ability> ability = player.useAbility(opponent);
        game.render(*ability.get());
        game.render(opponent.field);
    }
    
    void PlayerActionState::mark()
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        opponent.field.mark(player.cursor);
        game.render(opponent.field);
    }
    
    void PlayerActionState::move(InputMessage message)
    {
        Player &player = game.getPlayer();

        if (handleXYInput(player.cursor, message)) {
            game.render(bbox2(player.cursor, player.cursor + vec2(1, 1)));
        }
    }


    void PlayerActionState::handle(InputMessage message)
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();

        try {
            switch (message.kind) {
            case seabattle::InputMessage::PRIMARY_ACTION:   attack(); break;
            case seabattle::InputMessage::SECONDARY_ACTION: useAbility(); break;
            case seabattle::InputMessage::TERTIARY_ACTION:  mark(); break;
            default:                                        move(message); break;
            }
        }
        catch (SeabattleException &e) {
            game.render(e.what());
        }
    }

    static StateRegistration<PlayerActionState> registration;
    std::string_view PlayerActionState::getName() const { return name; }
}
