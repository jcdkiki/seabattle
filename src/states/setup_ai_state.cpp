#include "setup_ai_state.hpp"
#include "game.hpp"
#include "player_action_state.hpp"

namespace seabattle {
    SetupAIState::SetupAIState(Game &game) : GameState(game)
    {
        Player &player = game.getPlayer();
        Player &opponent = game.getOpponent();
        
        vec2 field_size = player.field.getSize();
        opponent.field = Field(field_size);

        std::vector<size_t> ship_sizes;
        for (Ship &ship : player.ships) {
            ship_sizes.push_back(ship.getSize());
        }

        opponent.ships = ShipManager(ship_sizes.begin(), ship_sizes.end());

        for (Ship &ship : opponent.ships) {
            size_t size = ship.getSize();
            
            vec2 request = vec2(1, size);
            Ship::Orientation orientation = Ship::Orientation::VERTICAL;
            if (rand() & 1) {
                orientation = Ship::Orientation::HORIZONTAL;
                request = vec2(size, 1);
            }
            
            std::vector<vec2> good_pos;

            for (int y = 0; y < field_size.y - request.y + 1; y++) {
                for (int x = 0; x < field_size.x - request.x + 1; x++) {
                    bool ok = true;
                    for (int w = -1; w <= request.x; w++) {
                        for (int h = -1; h <= request.y; h++) {
                            if (x + w < 0 || x + w >= field_size.x || y + h < 0 || y + h >= field_size.y)
                                continue;
                            
                            if (opponent.field[vec2(x + w, y + h)].ship_segment) {
                                ok = false;
                                break;
                            }
                        }
                    }

                    if (ok) {
                        good_pos.push_back(vec2(x, y));
                    }
                }
            }

            vec2 pos = good_pos[rand() % good_pos.size()];
            opponent.field.addShip(ship, pos, orientation);
        }

        game.render("Press primary key to FIGHT!!!");
    }

    void SetupAIState::primaryAction()
    {
        game.updateState(new PlayerActionState(game));
    }

    static StateRegistration<SetupAIState> registration;
    std::string_view SetupAIState::getName() const { return name; }
}
