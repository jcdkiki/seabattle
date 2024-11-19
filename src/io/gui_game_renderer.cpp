#include "gui_game_renderer.hpp"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <climits>

namespace seabattle {
    static constexpr rgba32 CLEAR_COLOR(255, 255, 255);
    static constexpr rgba32 MESSAGE_COLOR(0, 0, 0);
    static constexpr rgba32 FOG_COLOR(127, 127, 127);
    static constexpr rgba32 FULL_SHIP_COLOR(0, 255, 0);
    static constexpr rgba32 DAMAGED_SHIP_COLOR(180, 180, 0);
    static constexpr rgba32 DESTROYED_SHIP_COLOR(255, 0, 0);
    static constexpr rgba32 UNKNOWN_COLOR(0xCD, 0, 0xCD);
    static constexpr rgba32 DOUBLEDAMAGE_COLOR(255, 0, 0);
    static constexpr rgba32 SCANNER_COLOR(0, 0, 255);
    static constexpr rgba32 SNEAKY_ATTACK_COLOR(0, 255, 0);
    static constexpr rgba32 CURSOR_COLOR(0, 0, 0);
    constexpr static int FONT_SIZE = 20;

    static constexpr vec2 FIELD_POSITION(16, 16);
    static constexpr vec2 CELL_SIZE(16, 16);

    void GUIGameRenderer::drawField()
    {
        for (int y = 0; y < field_size.y; y++) {
            for (int x = 0; x < field_size.x; x++) {
                rgba32 col = field_color[x + y*field_size.x];
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

                SDL_Rect rect = {
                    .x = FIELD_POSITION.x + CELL_SIZE.x * x,
                    .y = FIELD_POSITION.y + CELL_SIZE.y * y,
                    .w = CELL_SIZE.x, .h = CELL_SIZE.y
                };

                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    void GUIGameRenderer::drawTint()
    {
        if (cur_time > tint_time + 500) {
            return;
        }

        float alpha = (float)(tint_time + 500 - cur_time) / 500.f;
        SDL_SetRenderDrawColor(renderer, tint_color.r, tint_color.g, tint_color.b, tint_color.a * alpha);
        
        SDL_Rect rect;
        SDL_RenderGetClipRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

    void GUIGameRenderer::drawMessages()
    {
        for (int i = 0; i < N_MESSAGES; i++) {
            int message_index = (current_message - i + N_MESSAGES) % N_MESSAGES;

            if (messages[message_index].text.empty())
                continue;

            int extent, count;
            TTF_MeasureUTF8(font, messages[message_index].text.c_str(), INT_MAX, &extent, &count);

            float alpha;
            if (cur_time > messages[message_index].time + 500)
                alpha = 0.f;
            else
                alpha = 1.f - (float)(cur_time - messages[message_index].time) / 500;
            
            SDL_Color color = { MESSAGE_COLOR.r, MESSAGE_COLOR.g, MESSAGE_COLOR.b, (unsigned char)(MESSAGE_COLOR.a * alpha) };
            SDL_Surface *surface = TTF_RenderUTF8_Solid(font, messages[message_index].text.c_str(), color);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            int window_w, window_h;
            SDL_GetWindowSize(window, &window_w, &window_h);

            SDL_Rect dst_rect = surface->clip_rect;
            dst_rect.x = 16;
            dst_rect.y = window_h - 16 - (i + 1)*(FONT_SIZE + 2);

            SDL_RenderCopy(renderer, texture, &surface->clip_rect, &dst_rect);
            
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
    }

    void GUIGameRenderer::drawCursor()
    {
        SDL_SetRenderDrawColor(renderer, CURSOR_COLOR.r, CURSOR_COLOR.b, CURSOR_COLOR.b, CURSOR_COLOR.a);
        
        SDL_Rect rect = {
            .x = FIELD_POSITION.x + cursor.min.x * CELL_SIZE.x,
            .y = FIELD_POSITION.y + cursor.min.y * CELL_SIZE.y,
            .w = (cursor.max.x - cursor.min.x) * CELL_SIZE.x,
            .h = (cursor.max.y - cursor.min.y) * CELL_SIZE.y
        };
        
        SDL_RenderDrawRect(renderer, &rect);
    }

    void GUIGameRenderer::update()
    {
        SDL_SetRenderDrawColor(renderer, CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
        SDL_RenderClear(renderer);
        
        cur_time = SDL_GetTicks64();
        this->drawField();
        this->drawCursor();
        this->drawTint();
        this->drawMessages();


        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    void GUIGameRenderer::operator<<(std::string_view text)
    {
        current_message = (current_message + 1) % N_MESSAGES;
        messages[current_message].text = text;
        messages[current_message].time = SDL_GetTicks64();
    }

    void GUIGameRenderer::operator<<(const Field &field)
    {
        if (field_size != field.getSize()) {
            field_size = field.getSize();
            field_color = new rgba32[field_size.x * field_size.y];
        }

        vec2 size = field.getSize();
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                const Field::Cell &cell = field[vec2(x, y)];
                rgba32 col(0, 0, 0);
                if (cell.has_fog) {
                    col = FOG_COLOR;
                }
                else if (cell.ship_segment) {
                    switch (*cell.ship_segment) {
                        case Ship::SegmentState::FULL:      col = FULL_SHIP_COLOR; break;
                        case Ship::SegmentState::DAMAGED:   col = DAMAGED_SHIP_COLOR; break;
                        case Ship::SegmentState::DESTROYED: col = DESTROYED_SHIP_COLOR; break;
                        default:                            col = UNKNOWN_COLOR; break;
                    }
                }

                field_color[x + y*size.x] = col;
            }
        }
    }

    void GUIGameRenderer::operator<<(bbox2 cursor)
    {
        this->cursor = cursor;
    }

    GUIGameRenderer::GUIGameRenderer()
    {
        if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
            throw std::runtime_error("Error initializing SDL: " + std::string(SDL_GetError()));
        } 

        if (TTF_Init() < 0)
        {
            throw std::runtime_error("Error in initializing SDL TTF: " + std::string(SDL_GetError()));
        }

        window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            throw std::runtime_error("Error creating window: " + std::string(SDL_GetError()));
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (renderer == nullptr) {
            throw std::runtime_error("Error creating renderer: " + std::string(SDL_GetError()));
        }

        font = TTF_OpenFont("assets/font.ttf", FONT_SIZE);
        current_message = N_MESSAGES - 1;

        field_size = vec2(0, 0);
        field_color = nullptr;
    }

    void GUIGameRenderer::setTint(rgba32 color)
    {
        tint_color = color;
        tint_time = SDL_GetTicks64();
    }

    void GUIGameRenderer::operator<<(const DoubleDamage &ability)
    {
        (*this) << "You were blessed with double damage!!!!";
        setTint(DOUBLEDAMAGE_COLOR);
    }

    void GUIGameRenderer::operator<<(const SneakyAttack &ability)
    {
        (*this) << "Sneaky attack was performed successfully!!!";
        setTint(SNEAKY_ATTACK_COLOR);
    }

    void GUIGameRenderer::operator<<(const Scanner &ability)
    {
        if (ability.isFound()) {
            (*this) << "Found ship here!!!!";
        }
        else {
            (*this) << "Nothing here :((((";
        }

        (*this) << bbox2(ability.getPosition(), ability.getPosition() + vec2(2, 2));
        setTint(SCANNER_COLOR);
    }

    GUIGameRenderer::~GUIGameRenderer()
    {
        delete field_color;

        TTF_CloseFont(font);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
}
