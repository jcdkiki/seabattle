#ifndef SEABATTLE_SETUP_FIELD_CONTROL_HPP_
#define SEABATTLE_SETUP_FIELD_CONTROL_HPP_

#include "game_control.hpp"
#include "setup_ships_control.hpp"
#include "messaging/game_messages.hpp"

namespace seabattle {
    class SetupFieldControl : public GameControl {
        vec2 size;
    public:
        SetupFieldControl(GameState &state) : GameControl(state)
        {
            emplace<LogMessage>("Welcome to seabattle. Select field size");
        }

        void handleInput(std::unique_ptr<const InputMessage> msg)
        {
            if (handleXYInput(size, *msg)) {
                emplace<RenderFieldPreviewMessage>(size);
                return;
            }

            if (msg->action == InputMessage::PRIMARY_ACTION) {
                try {
                    state.player.field = Field(size);
                }
                catch (std::invalid_argument &e) {
                    emplace<LogMessage>(e.what());
                    return;
                }

                emplace<ChangeControlMessage>(new SetupShipsControl(state));
            }
        }
    };
}

#endif
