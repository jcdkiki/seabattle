#include "gui_output_device.hpp"
#include <SDL_timer.h>
#include <climits>

namespace seabattle {
    void GUIOutputDevice::update()
    {
        uint64_t cur_time = SDL_GetTicks64();
        if (cur_time < log_time + 500) {
            int extent, count;
            TTF_MeasureUTF8(font, log_message.c_str(), INT_MAX, &extent, &count);

            SDL_Rect rect = {
                .x = 10, .y = win_surface->h - 10 - 32,
                .w = win_surface->w - 10, .h = 10 + 32
            };

            float alpha = 1.f - (float)(cur_time - log_time) / 500;
            SDL_Color color = { (Uint8)(255*alpha), (Uint8)(255*alpha), (Uint8)(255*alpha), 255 };

            SDL_FillRect(win_surface, &rect, SDL_MapRGB(win_surface->format, 127, 127, 127));
            SDL_Surface *surface = TTF_RenderUTF8_Solid(font, log_message.c_str(), color);

            rect.w = extent;

            SDL_UpperBlit(surface, &surface->clip_rect, win_surface, &rect);
            SDL_FreeSurface(surface);
        }

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
        
    void GUIOutputDevice::drawField(vec2 pos, const Field &field, bbox2 cursor)
    {
        vec2 size = field.getSize();
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                const Field::Cell &cell = field[vec2(x, y)];
                Uint32 col;
                if (cell.has_fog) {
                    col = 0x606060FF;
                }
                else if (cell.ship_segment) {
                    switch (*cell.ship_segment) {
                        case Ship::SegmentState::FULL:      col = 0x10C010FF; break;
                        case Ship::SegmentState::DAMAGED:   col = 0x808010FF; break;
                        case Ship::SegmentState::DESTROYED: col = 0xC01010FF; break;
                        default:                            col = 0x7F7F7FFF; break;
                    }
                }
                else {
                    col = 0x000000FF;
                }

                SDL_Rect rect = {
                    .x = pos.x + x*16,
                    .y = pos.y + y*16,
                    .w = 16, .h = 16
                };

                if (cursor.contains(vec2(x, y))) {
                    col |= 0x00FF0000;
                }

                SDL_FillRect(win_surface, &rect, SDL_MapRGB(win_surface->format, (col >> 24) & 0xFF, (col >>16) & 0xFF, (col >> 8) & 0xFF));
            }
        }
    }

    void GUIOutputDevice::handleLogMessage(std::unique_ptr<const LogMessage> msg)
    {
        log_message = msg->text;
        log_time = SDL_GetTicks64();
    }

    void GUIOutputDevice::handleRenderFieldMessage(std::unique_ptr<const RenderFieldMessage> msg)
    {
        vec2 pos;
        if (msg->location == RenderFieldMessage::LEFT) {
            pos = vec2(10, 10);
        }
        else {
            pos = vec2(20, 10) + msg->field.getSize() * 16;
        }

        drawField(pos, msg->field, msg->cursor);
    }

    void GUIOutputDevice::handleRenderFieldPreviewMessage(std::unique_ptr<const RenderFieldPreviewMessage> msg)
    {
        SDL_Rect rect = {
            .x = 10, .y = 10,
            .w = msg->size.x * 16, .h = msg->size.y * 16
        };
        SDL_FillRect(win_surface, &rect, SDL_MapRGB(win_surface->format, 160, 160, 0));
    }

    GUIOutputDevice::GUIOutputDevice()
    {
        registerHandler<LogMessage>((HandlerMethod)&GUIOutputDevice::handleLogMessage);
        registerHandler<RenderFieldMessage>((HandlerMethod)&GUIOutputDevice::handleRenderFieldMessage);
        registerHandler<RenderFieldPreviewMessage>((HandlerMethod)&GUIOutputDevice::handleRenderFieldPreviewMessage);

        if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
            throw std::runtime_error("Error initializing SDL: " + std::string(SDL_GetError()));
        } 

        if (TTF_Init() < 0)
        {
            throw std::runtime_error("Error in initializing SDL TTF: " + std::string(SDL_GetError()));
        }

        window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            throw std::runtime_error("Error creating window: " + std::string(SDL_GetError()));
        }

        win_surface = SDL_GetWindowSurface(window);

        if (win_surface == nullptr) {
            throw std::runtime_error("Error getting surface: " + std::string(SDL_GetError()));
        }

        SDL_FillRect(win_surface, NULL, SDL_MapRGB(win_surface->format, 127, 127, 127));
        SDL_UpdateWindowSurface(window);

        font = TTF_OpenFont("assets/font.ttf", 32);
    }
    
    GUIOutputDevice::~GUIOutputDevice()
    {
        TTF_CloseFont(font);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
}
