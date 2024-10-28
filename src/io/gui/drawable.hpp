#ifndef SEABATTLE_DRAWABLE_HPP_
#define SEABATTLE_DRAWABLE_HPP_

#include "renderer_context.hpp"

namespace seabattle {
    class Drawable {
    private:
        friend class GUIGameRenderer;
        virtual void draw(const RendererContext &renderer) = 0;
    };
}

#endif
