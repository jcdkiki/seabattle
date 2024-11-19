#ifndef TUI_GAME_RENDERER_H
#define TUI_GAME_RENDERER_H

#include "game_renderer.hpp"

namespace seabattle {
    class TUIGameRenderer : public GameRenderer {
        bbox2 cursor;
    public:
        void operator<<(const DoubleDamage &ability);
        void operator<<(const SneakyAttack &ability);
        void operator<<(const Scanner &ability);

        void operator<<(const Field &field);
        void operator<<(bbox2 cursor);
        void operator<<(std::string_view text);
        void update() {}        
    };
}

#endif // TUI_GAME_RENDERER_H
