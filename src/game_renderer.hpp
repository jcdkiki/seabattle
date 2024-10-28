#ifndef SEABATTLE_GAME_RENDERER_HPP_
#define SEABATTLE_GAME_RENDERER_HPP_

#include "field.hpp"
#include <memory>
#include <string_view>

namespace seabattle {
    class GameRenderer {
    public:
        virtual void operator<<(const Field &field) = 0;
        virtual void operator<<(bbox2 cursor) = 0;
        virtual void operator<<(std::string_view text) = 0;
        virtual void update() = 0;
    };
}

#endif
