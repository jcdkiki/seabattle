#ifndef SEABATTLE_CONTROL_GAME_STATE_HPP_
#define SEABATTLE_CONTROL_GAME_STATE_HPP_

#include "input/message.hpp"
#include "state_registry.hpp"
#include "state_registration.hpp"
#include "vec2.hpp"

namespace seabattle {
    class Game;

    class GameState {
    protected:
        Game &game;
        
        bool handleXYInput(vec2 &vec, const InputMessage msg);
        bool handleXInput(int &x, const InputMessage msg);

        virtual void load(std::istream &is);
        virtual void save(std::ostream &os);

    public:
        GameState(Game &game) : game(game) {}
        virtual ~GameState() {};
    
        virtual void handle(InputMessage message) = 0;
        virtual std::string_view getName() const = 0;

        friend std::ostream &operator<<(std::ostream &os, GameState &game) { game.save(os); return os; }
        friend std::istream &operator>>(std::istream &is, GameState &game) { game.load(is); return is; }
    };
}

#endif
