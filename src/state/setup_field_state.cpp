#include "setup_field_state.hpp"
#include "setup_ships_state.hpp"
#include "game.hpp"

#include <string>

namespace seabattle {
    SetupFieldState::SetupFieldState(Game &ctx) : GameState(ctx)
    {
        ctx << "Welcome to seabattle. Select field size";
    }

    void SetupFieldState::operator<<(AtomicInputMessage message)
    {
        if (handleXYInput(size, message)) {
            ctx << ("Field size: " + std::to_string(size.x) + 'x' + std::to_string(size.y));
        }
        else if (message.kind == AtomicInputMessage::PRIMARY_ACTION) {
            try {
                player().field = Field(size);
                ctx.changeState(new SetupShipsState(ctx));
            }
            catch (std::invalid_argument &e) {
                ctx << e.what();
                return;
            }

        }
    }
}
