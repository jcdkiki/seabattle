#ifndef SEABATTLE_DEVICES_GUI_OUTPUT_DEVICE_HPP_
#define SEABATTLE_DEVICES_GUI_OUTPUT_DEVICE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "messaging.hpp"
#include "messages.hpp"

namespace seabattle {
    class GUIOutputDevice : public MessageReciever {
        SDL_Surface *win_surface;
        SDL_Window *window;
        TTF_Font *font;

        uint64_t log_time;
        std::string log_message;

        void drawField(vec2 pos, const Field &field, bbox2 cursor);
    
        void handleLogMessage(std::unique_ptr<const LogMessage> msg);
        void handleRenderFieldMessage(std::unique_ptr<const RenderFieldMessage> msg);
        void handleRenderFieldPreviewMessage(std::unique_ptr<const RenderFieldPreviewMessage> msg);
    public:
        GUIOutputDevice();
        ~GUIOutputDevice();

        void update();
    };
}

#endif
