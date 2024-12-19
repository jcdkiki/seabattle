#ifndef SEABATTLE_RENDER_MESSAGE_HPP_
#define SEABATTLE_RENDER_MESSAGE_HPP_

#include "renderer/game_renderer.hpp"

namespace seabattle {
    struct AbstractRenderMessage {
        virtual void execute(GameRenderer &renderer) = 0;
        virtual ~AbstractRenderMessage() {};
    };

    template<class T>
    struct RenderMessage : public AbstractRenderMessage {
        T object;
        RenderMessage(const T &object) : object(object) {}
        void execute(GameRenderer &renderer) { renderer.handle(object); }
    };
};

#endif
