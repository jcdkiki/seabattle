#include "setup_ships_state.hpp"
#include "place_ships_state.hpp"
#include "game.hpp"
#include "ship.hpp"

#include <istream>
#include <ostream>

namespace seabattle {
    void SetupShipsState::showPoints()
    {
        game.render("You have " + std::to_string(points) + " points");
    }

    bool SetupShipsState::canPlace()
    {
        return size > 0 && size <= Ship::MAX_SIZE && points > (6 + 3*size);
    }

    SetupShipsState::SetupShipsState(Game &game) : GameState(game), size(0)
    {
        Player &player = game.getPlayer();
        
        vec2 field_size = player.field.getSize();
        points = field_size.x * field_size.y;

        game.render("Select ship sizes!");
        showPoints();
    }

    void SetupShipsState::handle(InputMessage message)
    {
        Player &player = game.getPlayer();

        if (message.kind == InputMessage::PRIMARY_ACTION) {
            if (canPlace()) {
                ship_sizes.push_back(size);
                points -= 6 + size*3;
                game.render("Added ship. Now create another one or proceed to the next stage");
            }
            else {
                game.render("Invalid ship size. Try again");
            }
            showPoints();
        }
        else if (message.kind == InputMessage::SECONDARY_ACTION) {
            try {
                player.ships = ShipManager(ship_sizes.begin(), ship_sizes.end());
                game.updateState(new PlaceShipsState(game));
            }
            catch (std::invalid_argument &e) {
                game.render(std::string("Error: ") + e.what() + " | Try again.");
                game.updateState(new SetupShipsState(game));
            }
        }
        else if (handleXInput(size, message)) {
            game.render("Ship size: " + std::to_string(size)); 
        }
    }

    void SetupShipsState::load(std::istream &is)
    {
        size_t n_sizes;
        is >> points >> size >> n_sizes;

        ship_sizes.resize(n_sizes);
        for (auto &x : ship_sizes) is >> x;
    }

    void SetupShipsState::save(std::ostream &os)
    {
        os << points << ' ' << size << ' ' << ship_sizes.size() << ' ';
        for (auto &x : ship_sizes) os << x << ' ';
    }

    static StateRegistration<SetupShipsState> registration;
    std::string_view SetupShipsState::getName() const { return name; }
}
