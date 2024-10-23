#include "setup_field_control.hpp"
#include "messaging/render_messages.hpp"
#include "setup_ships_control.hpp"

namespace seabattle {
    SetupFieldControl::SetupFieldControl(GameState &state) : GameControl(state)
    {
        emplace<LogMessage>("Welcome to seabattle. Select field size");
    }

    void SetupFieldControl::handleInput(std::unique_ptr<const InputMessage> msg)
    {
        if (handleXYInput(size, *msg)) {
            emplace<RenderFieldPreviewMessage>(size);
            emplace<LogMessage>("Field size: " + std::to_string(size.x) +'x' + std::to_string(size.y));
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
}
