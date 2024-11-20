#ifndef TUI_GAME_RENDERER_H
#define TUI_GAME_RENDERER_H

#include "game_renderer.hpp"

namespace seabattle {
    class TUIGameRenderer : public GameRenderer {
        bbox2 cursor;
    public:
        void handle(const DoubleDamage &ability);
        void handle(const SneakyAttack &ability);
        void handle(const Scanner &ability);

        void handle(const Field &field);
        void handle(bbox2 cursor);
        void handle(std::string_view text);
        
        void update() {}        
    };
}

#endif // TUI_GAME_RENDERER_H
