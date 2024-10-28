#ifndef SEABATTLE_GUI_GAME_RENDERER_HPP_
#define SEABATTLE_GUI_GAME_RENDERER_HPP_

#include "game_renderer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace seabattle {
    class Drawable;

    class GUIGameRenderer : public GameRenderer {
        SDL_Surface *win_surface;
        SDL_Window *window;
        TTF_Font *font;

        constexpr static int FONT_SIZE = 20;
        constexpr static int N_MESSAGES = 4;
        uint64_t log_time[4];
        std::string log_message[4];
        int current_message;
        uint64_t cursor_time;
        bbox2 cursor;;

        void drawField(vec2 pos, const Field &field);
    public:
        GUIGameRenderer();
        ~GUIGameRenderer();

        void operator<<(const Field &field);
        void operator<<(bbox2 cursor);
        void operator<<(std::string_view text);
        void update();
    };
}

#endif
