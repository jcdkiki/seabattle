#ifndef SEABATTLE_RENDER_PIPE_HPP_
#define SEABATTLE_RENDER_PIPE_HPP_

#include "game.hpp"

namespace seabattle {
    template <class T>
    class RenderPipe {
        Game &game;
        T renderer;
    public:

        RenderPipe(Game &game) : game(game) {}

        void pipeMessages()
        {
            for (const auto &render_message : game.render_queue) {
                render_message->execute(renderer);
            }

            renderer.update();
            game.render_queue.clear();
        }
    };
};

#endif
