#ifndef SEABATTLE_GAME_HPP_
#define SEABATTLE_GAME_HPP_

#include "messaging/message_pipe.hpp"
#include "messaging/game_messages.hpp"
#include "game_state.hpp"
#include "control/game_control.hpp"

namespace seabattle {
    class Game : public MessagePipe {
    protected:
        GameState state;
        std::unique_ptr<GameControl> control;
        bool is_running;

    public:
        Game();
        inline bool isRunning() { return is_running; }

        void handleInput(std::unique_ptr<const InputMessage> msg);
        void handleChangeControl(std::unique_ptr<const ChangeControlMessage> msg);
        void update(MessageGenerator &input, MessageReciever &output);
    };
}

#endif
