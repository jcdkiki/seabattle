#include "setup_field_state.hpp"
#include "setup_ships_state.hpp"
#include "game.hpp"

#include <string>

namespace seabattle {
    SetupFieldState::SetupFieldState(Game &game) : GameState(game)
    {
        game.getPlayer() = Player();
        game.getOpponent() = Player();

        game.render("Welcome to seabattle. Select field size");
        game.render(bbox2(vec2(0, 0), vec2(0, 0)));
    }

    void SetupFieldState::handle(InputMessage message)
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();
        
        if (handleXYInput(size, message)) {
            game.render("Field size: " + std::to_string(size.x) + 'x' + std::to_string(size.y));
            game.render(bbox2(vec2(0, 0), size));
        }
        else if (message.kind == InputMessage::PRIMARY_ACTION) {
            try {
                player.field = Field(size);
                opponent.field = Field(size);
                game.getAIController() = AIController(&player.field);
                game.updateState(new SetupShipsState(game));
            }
            catch (std::invalid_argument &e) {
                game.render(e.what());
                return;
            }

        }
    }

    static StateRegistration<SetupFieldState> registration;
    std::string_view SetupFieldState::getName() const { return name; }
}
