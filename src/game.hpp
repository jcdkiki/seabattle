#ifndef SEABATTLE_GAME_CONTEXT_HPP_
#define SEABATTLE_GAME_CONTEXT_HPP_

#include "ai_controller.hpp"
#include "player.hpp"
#include "states/game_state.hpp"
#include "renderer/game_renderer.hpp"
#include "renderer/render_message.hpp"
#include <memory>

namespace seabattle {
    class Game {
    public:
        std::vector<std::unique_ptr<AbstractRenderMessage>> render_queue;
        
        Game();
        Game(const Game &ctx) = delete;
        Game(Game &&ctx) = delete;
        ~Game();

        template<class T>
        void render(const T &object)
        {
            render_queue.emplace_back(new RenderMessage<T>(object));
        }

        void render(const char *text)
        {
            render_queue.emplace_back(new RenderMessage<std::string>(text));
        }

        void updateState(GameState *new_state);
        
        inline Player &getOpponent() { return opponent; }
        inline Player &getPlayer() { return player; }
        inline bool isRunning() { return is_running; }
        inline AIController &getAIController() { return ai; }

        friend std::ostream &operator<<(std::ostream &os, Game &game);
        friend std::istream &operator>>(std::istream &is, Game &game);
        
        void quit();
        void save();
        void load();

        void primaryAction() { state->primaryAction(); }
        void secondaryAction() { state->secondaryAction(); };
        void tertiaryAction() { state->tertiaryAction(); };
        void moveCursor(vec2 amount) { state->moveCursor(amount); };
    
    private:
        GameRenderer *renderer;
        GameState *state;
        AIController ai;
        bool is_running;
        
        Player player;
        Player opponent;        
    };
}

#endif
