#include "place_ships_state.hpp"
#include "setup_ai_state.hpp"
#include "game.hpp"

#include <ostream>
#include <istream>

namespace seabattle {
    bbox2 PlaceShipsState::getCursor()
    {
        bbox2 cursor(position, position);
        if (current_ship != game.getPlayer().ships.end()) {
            if (orientation == Ship::Orientation::HORIZONTAL)
                cursor.max += vec2(current_ship->getSize(), 1);
            else
                cursor.max += vec2(1, current_ship->getSize());
        }

        return cursor;
    }

    PlaceShipsState::PlaceShipsState(Game &game) : GameState(game)
    {
        Player &player = game.getPlayer();
        current_ship = player.ships.begin();

        game.render("Great job, now place your ships");
        game.render(player.field);
    }

    void PlaceShipsState::primaryAction()
    {
        Player &player = game.getPlayer();

        try {
            player.field.addShip(*current_ship, position, orientation, true);
            game.render(player.field);
            current_ship++;
        }
        catch (IllegalShipPositionException &e) {
            game.render(e.what());
        }

        if (current_ship == player.ships.end()) {
            player.field.coverInFog();
            game.updateState(new SetupAIState(game));
        }
    }

    void PlaceShipsState::secondaryAction()
    {
        orientation = (orientation == Ship::Orientation::HORIZONTAL) ? Ship::Orientation::VERTICAL : Ship::Orientation::HORIZONTAL;
        game.render(getCursor());
    }

    void PlaceShipsState::moveCursor(vec2 amount)
    {
        position += amount;
        game.render(getCursor());
    }
    
    void PlaceShipsState::save(std::ostream &os)
    {
        os << (int)orientation << ' ' << position.x << ' ' << position.y << ' '
           << (current_ship - game.getPlayer().ships.begin());
    }

    void PlaceShipsState::load(std::istream &is)
    {
        int orientation;
        size_t current_ship;
        is >> orientation >> position.x >> position.y >> current_ship;

        this->orientation = static_cast<Ship::Orientation>(orientation);
        this->current_ship = game.getPlayer().ships.begin() + current_ship;
    }

    static StateRegistration<PlaceShipsState> registration;
    std::string_view PlaceShipsState::getName() const { return name; }
}
