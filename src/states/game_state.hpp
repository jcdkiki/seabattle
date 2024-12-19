#ifndef SEABATTLE_CONTROL_GAME_STATE_HPP_
#define SEABATTLE_CONTROL_GAME_STATE_HPP_

#include "state_registry.hpp"
#include "state_registration.hpp"
#include "vec2.hpp"

namespace seabattle {
    class Game;

    class GameState {
    protected:
        Game &game;
        
        virtual void load(std::istream &is);
        virtual void save(std::ostream &os);

    public:
        GameState(Game &game) : game(game) {}
        virtual ~GameState() {};
    
        virtual std::string_view getName() const = 0;

        virtual void primaryAction() {}
        virtual void secondaryAction() {}
        virtual void tertiaryAction() {}
        virtual void moveCursor(vec2 amount) {}        

        friend std::ostream &operator<<(std::ostream &os, GameState &game) { game.save(os); return os; }
        friend std::istream &operator>>(std::istream &is, GameState &game) { game.load(is); return is; }
    };
}

#endif
