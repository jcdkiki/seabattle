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

        uint64_t cur_time;

        rgba32 tint_color;
        uint64_t tint_time;

        constexpr static int N_MESSAGES = 4;
        Message messages[N_MESSAGES];
        int current_message;
        bbox2 cursor;

        vec2 field_size;
        rgba32 *field_color;

        void drawField();
        void drawTint();
        void drawCursor();
        void drawMessages();
        void setTint(rgba32 color);
    public:
        GUIGameRenderer();
        ~GUIGameRenderer();

        void operator<<(const DoubleDamage &ability);
        void operator<<(const SneakyAttack &ability);
        void operator<<(const Scanner &ability);

        void operator<<(const Field &field);
        void operator<<(bbox2 cursor);
        void operator<<(std::string_view text);
        void update();
    };
}

#endif
