#ifndef SEABATTLE_CONTROL_FIGHT_CONTROL_HPP_
#define SEABATTLE_CONTROL_FIGHT_CONTROL_HPP_

#include "game_control.hpp"

namespace seabattle {
    class FightControl : public GameControl {
    public:
        FightControl(GameState &state) : GameControl(state)
        {
            state.player.field.coverInFog();
            emplace<LogMessage>("Great job! Now it's time to FIGHT!!!!");

            bbox2 cursor(state.player.cursor, state.player.cursor + vec2(1, 1));
            emplace<RenderFieldMessage>(RenderFieldMessage::LEFT, state.player.field, cursor);
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
        {
            if (msg->action == InputMessage::PRIMARY_ACTION) {
                try {
                    state.player.attack(state.player);
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                }

                // AI attack code will be here
            }
            else if (msg->action == InputMessage::SECONDARY_ACTION) {
                try {
                    state.player.useAbility(state.player);
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                }
            }
            else handleXYInput(state.player.cursor, *msg);

            bbox2 cursor(state.player.cursor, state.player.cursor + vec2(1, 1));
            emplace<RenderFieldMessage>(RenderFieldMessage::LEFT, state.player.field, cursor);
        }
    };
}

#endif
