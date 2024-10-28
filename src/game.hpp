#ifndef SEABATTLE_GAME_CONTEXT_HPP_
#define SEABATTLE_GAME_CONTEXT_HPP_

#include "message_pipe.hpp"
#include "human_player.hpp"
#include "game_renderer.hpp"
#include "input_messages.hpp"
#include "state/game_state.hpp"

namespace seabattle {
    struct Game : public MessagePipe<GameRenderer> {
        GameState *state;
        bool is_running;
    
    protected:
        HumanPlayer player;
        Player opponent;
        friend class GameState;

    public:
        explicit Game(GameRenderer &renderer);
        Game(const Game &ctx) = delete;
        Game(Game &&ctx) = delete;
        ~Game();

        using MessagePipe::operator<<;
        void operator<<(AtomicInputMessage message);

        void changeState(GameState *new_state);
        
        inline void stop() { is_running = false; }
        inline bool isRunning() { return is_running; }
    };
}

#endif
