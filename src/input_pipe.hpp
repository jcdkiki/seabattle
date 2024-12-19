#ifndef SEABATTLE_INPUT_PIPE_HPP_
#define SEABATTLE_INPUT_PIPE_HPP_

#include "game.hpp"
#include "input/input_messages.hpp"
#include <memory>

namespace seabattle {
    template<class T>
    class InputPipe {
        Game &game;
        T game_input;

    public:
        InputPipe(Game &game) : game(game) {}

        void pipeMessages()
        {
            std::unique_ptr<InputMessage> msg(game_input.pollMessage());
            while (msg) {
                msg->execute(game);
                msg = std::unique_ptr<InputMessage>(game_input.pollMessage());
            }
        }
    };
}

#endif
