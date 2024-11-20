#ifndef SEABATTLE_GUI_GAME_RENDERER_HPP_
#define SEABATTLE_GUI_GAME_RENDERER_HPP_

#include "game_renderer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "gui/rgba32.hpp"

namespace seabattle {
    class Drawable;

    class GUIGameRenderer : public GameRenderer {
        SDL_Renderer *renderer;
        SDL_Window *window;
        TTF_Font *font;

        struct Message {
            uint64_t time;
            std::string text;
        };

        struct Cell {
            rgba32 color;
            bool marked : 1;
        };

        uint64_t cur_time;

        rgba32 tint_color;
        uint64_t tint_time;
        uint64_t shake_time;

        constexpr static int N_MESSAGES = 6;
        Message messages[N_MESSAGES];
        int current_message;
        bbox2 cursor;

        vec2 field_pos;
        vec2 field_size;
        Cell *field_data;

        void applyShake();
        void drawField();
        void drawTint();
        void drawCursor();
        void drawMessages();
        void setTint(rgba32 color);
        void setShake();
    public:
        GUIGameRenderer();
        ~GUIGameRenderer();

        void handle(const DoubleDamage &ability);
        void handle(const SneakyAttack &ability);
        void handle(const Scanner &ability);

        void handle(const Field &field);
        void handle(bbox2 cursor);
        void handle(std::string_view text);
        void update();
    };
}

#endif
