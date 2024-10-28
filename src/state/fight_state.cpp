#include "fight_state.hpp"
#include "game.hpp"

namespace seabattle {
    FightState::FightState(Game &ctx) : GameState(ctx)
    {
        player().field.coverInFog();
        ctx << "Great job! Now it's time to FIGHT!!!!";

        bbox2 cursor(player().cursor, player().cursor + vec2(1, 1));
        ctx << player().field;
    }

    void FightState::operator<<(AtomicInputMessage message)
    {
        if (message.kind == AtomicInputMessage::PRIMARY_ACTION) {
            try {
                player().attack(player());
                ctx << player().field;
            }
            catch (SeabattleException &e) {
                ctx << std::string(e.what());
            }
        }
        else if (message.kind == AtomicInputMessage::SECONDARY_ACTION) {
            try {
                player().useAbility(player());
                ctx << player().field;
            }
            catch (SeabattleException &e) {
                ctx << std::string(e.what());
            }
        }
        else if (handleXYInput(player().cursor, message)) {
            ctx << bbox2(player().cursor, player().cursor + vec2(1, 1));
        }
    }
}
