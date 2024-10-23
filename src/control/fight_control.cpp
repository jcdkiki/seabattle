#include "fight_control.hpp"

#include "exception.hpp"
#include "field.hpp"
#include "messaging/render_messages.hpp"

namespace seabattle {
    FightControl::FightControl(GameState &state) : GameControl(state)
    {
        state.player.field.coverInFog();
        emplace<LogMessage>("Great job! Now it's time to FIGHT!!!!");

        bbox2 cursor(state.player.cursor, state.player.cursor + vec2(1, 1));
        emplace<RenderFieldMessage>(state.player.field, cursor);
    }

    void FightControl::handleInput(std::unique_ptr<const InputMessage> msg)
    {
        if (msg->action == InputMessage::PRIMARY_ACTION) {
            try {
                state.player.attack(state.player);
            }
            catch (SeabattleException &e) {
                emplace<LogMessage>(e.what());
            }

            // AI attack code will be here maybe????
        }
        else if (msg->action == InputMessage::SECONDARY_ACTION) {
            try {
                state.player.useAbility(state.player);
            }
            catch (SeabattleException &e) {
                emplace<LogMessage>(e.what());
            }
        }
        else if (handleXYInput(state.player.cursor, *msg)) {
            emplace<RenderCursorMessage>(state.player.cursor);
        }

        bbox2 cursor(state.player.cursor, state.player.cursor + vec2(1, 1));
        emplace<RenderFieldMessage>(state.player.field, cursor);
    }
}
