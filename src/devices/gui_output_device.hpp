#ifndef SEABATTLE_DEVICES_GUI_OUTPUT_DEVICE_HPP_
#define SEABATTLE_DEVICES_GUI_OUTPUT_DEVICE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "messaging/message_reciever.hpp"
#include "messaging/render_messages.hpp"

namespace seabattle {
    class GUIOutputDevice : public MessageReciever {
        SDL_Surface *win_surface;
        SDL_Window *window;
        TTF_Font *font;

        constexpr static int FONT_SIZE = 20;
        constexpr static int N_MESSAGES = 4;
        uint64_t log_time[4];
        std::string log_message[4];
        int current_message;
        uint64_t cursor_time;
        vec2 cursor_position;

        void drawField(vec2 pos, const Field &field, bbox2 cursor);
    
        void handleLogMessage(std::unique_ptr<const LogMessage> msg);
        void handleRenderFieldMessage(std::unique_ptr<const RenderFieldMessage> msg);
        void handleRenderFieldPreviewMessage(std::unique_ptr<const RenderFieldPreviewMessage> msg);
        void handleRenderCursorMessage(std::unique_ptr<const RenderCursorMessage> msg);
    public:
        GUIOutputDevice();
        ~GUIOutputDevice();

        void update();
    };
}

#endif
