#ifndef SEABATTLE_GAME_CONTEXT_HPP_
#define SEABATTLE_GAME_CONTEXT_HPP_

#include "ai_controller.hpp"
#include "player.hpp"
#include "renderer/game_renderer.hpp"
#include "states/game_state.hpp"

namespace seabattle {
    class Game {
        GameRenderer &renderer;
        GameState *state;
        AIController ai;
        bool is_running;
        
        Player player;
        Player opponent;
        
        bool is_state_new;

    public:
        explicit Game(GameRenderer &renderer);
        Game(const Game &ctx) = delete;
        Game(Game &&ctx) = delete;
        ~Game();

        template<class T>
        void render(const T &object)
        {
            renderer.handle(object);
        }

        void updateState(GameState *new_state);
        void handle(InputMessage message);
        
        inline void stop() { is_running = false; }
        
        inline Player &getPlayer() { return player; }
        inline Player &getOpponent() { return opponent; }
        inline AIController &getAIController() { return ai; }
        inline bool isRunning() { return is_running; }

        friend std::ostream &operator<<(std::ostream &os, Game &game);
        friend std::istream &operator>>(std::istream &is, Game &game);

        void save();
        void load();
    };
}

#endif
