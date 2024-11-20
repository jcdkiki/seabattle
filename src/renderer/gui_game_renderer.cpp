#include "gui_game_renderer.hpp"
#include <SDL_blendmode.h>
#include <SDL_render.h>
#include <climits>

namespace seabattle {
    static constexpr rgba32 CLEAR_COLOR(255, 255, 255);
    static constexpr rgba32 MESSAGE_COLOR(0, 0, 0);
    static constexpr rgba32 FOG_COLOR(127, 127, 127);
    static constexpr rgba32 FULL_SHIP_COLOR(0, 255, 0);
    static constexpr rgba32 DAMAGED_SHIP_COLOR(180, 180, 0);
    static constexpr rgba32 DESTROYED_SHIP_COLOR(255, 127, 127);
    static constexpr rgba32 EMPTY_COLOR(127, 127, 255);
    static constexpr rgba32 DOUBLEDAMAGE_COLOR(255, 0, 0);
    static constexpr rgba32 SCANNER_COLOR(0, 0, 255);
    static constexpr rgba32 SNEAKY_ATTACK_COLOR(0, 255, 0);
    static constexpr rgba32 CURSOR_COLOR(0, 0, 0);
    constexpr static int FONT_SIZE = 18;

    static constexpr vec2 FIELD_POSITION(16, 16);
    static constexpr vec2 CELL_SIZE(32, 32);

    void GUIGameRenderer::applyShake()
    {
        field_pos = FIELD_POSITION;

        if (shake_time + 500 > cur_time) {
            float shake_amount = (shake_time + 500 - cur_time) / 500.f * 30.f;
            vec2 offset(
                ((double)rand() / RAND_MAX - 0.5f) * shake_amount,
                ((double)rand() / RAND_MAX - 0.5f) * shake_amount
            );

            field_pos += offset;
        }
    }

    void GUIGameRenderer::drawField()
    {
        for (int y = 0; y < field_size.y; y++) {
            for (int x = 0; x < field_size.x; x++) {
                rgba32 col = field_data[x + y*field_size.x].color;
                SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);

                SDL_Rect rect = {
                    .x = field_pos.x + CELL_SIZE.x * x,
                    .y = field_pos.y + CELL_SIZE.y * y,
                    .w = CELL_SIZE.x, .h = CELL_SIZE.y
                };

                SDL_RenderFillRect(renderer, &rect);

                SDL_SetRenderDrawColor(renderer, CURSOR_COLOR.r, CURSOR_COLOR.g, CURSOR_COLOR.b, CURSOR_COLOR.a / 4);
                SDL_RenderDrawRect(renderer, &rect);

                if (field_data[x + y*field_size.x].marked) {
                    SDL_SetRenderDrawColor(renderer, CURSOR_COLOR.r, CURSOR_COLOR.g, CURSOR_COLOR.b, CURSOR_COLOR.a / 2);
                    SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + CELL_SIZE.x, rect.y + CELL_SIZE.y);
                    SDL_RenderDrawLine(renderer, rect.x + CELL_SIZE.x, rect.y, rect.x, rect.y + CELL_SIZE.y);
                }
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

            SDL_Color color = { MESSAGE_COLOR.r, MESSAGE_COLOR.g, MESSAGE_COLOR.b, MESSAGE_COLOR.a };
            SDL_Surface *surface = TTF_RenderUTF8_Solid(font, messages[message_index].text.c_str(), color);
            
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            
            int window_w, window_h;
            SDL_GetWindowSize(window, &window_w, &window_h);

            SDL_Rect dst_rect = surface->clip_rect;

            int diff = messages[message_index].time + 250 - cur_time;
            if (diff > 0) {
                float coeff = diff / 250.f;
                dst_rect.x = 16 - (surface->w + 16) * coeff*coeff;
            }
            else {
                dst_rect.x = 16;
            }
            
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
            .x = field_pos.x + cursor.min.x * CELL_SIZE.x,
            .y = field_pos.y + cursor.min.y * CELL_SIZE.y,
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
        this->applyShake();
        this->drawField();
        this->drawCursor();
        this->drawTint();
        this->drawMessages();


        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    void GUIGameRenderer::handle(std::string_view text)
    {
        current_message = (current_message + 1) % N_MESSAGES;
        messages[current_message].text = text;
        messages[current_message].time = SDL_GetTicks64();
    }

    void GUIGameRenderer::handle(const Field &field)
    {
        if (field_size != field.getSize()) {
            delete [] field_data;
            field_size = field.getSize();
            field_data = new Cell[field_size.x * field_size.y];
        }

        vec2 size = field.getSize();
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                const Field::Cell &cell = field[vec2(x, y)];
                rgba32 col = EMPTY_COLOR;
                if (cell.has_fog) {
                    col = FOG_COLOR;
                }
                else if (cell.ship_segment) {
                    switch (*cell.ship_segment) {
                        case Ship::SegmentState::FULL:      col = FULL_SHIP_COLOR; break;
                        case Ship::SegmentState::DAMAGED:   col = DAMAGED_SHIP_COLOR; break;
                        case Ship::SegmentState::DESTROYED: col = DESTROYED_SHIP_COLOR; break;
                        default:                            col = EMPTY_COLOR; break;
                    }
                }

                field_data[x + y*size.x].color = col;
                field_data[x + y*size.x].marked = cell.marked;
            }
        }
    }

    void GUIGameRenderer::handle(bbox2 cursor)
    {
        this->cursor = cursor;
    }

    GUIGameRenderer::GUIGameRenderer()
    {
        if (SDL_Init( SDL_INIT_EVERYTHING ) < 0) {
            throw std::runtime_error("Failed to init SDL: " + std::string(SDL_GetError()));
        } 

        if (TTF_Init() < 0)
        {
            throw std::runtime_error("Failed to init SDL TTF: " + std::string(SDL_GetError()));
        }

        window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
        }
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        font = TTF_OpenFont("data/font.ttf", FONT_SIZE);
        if (font == nullptr) {
            throw std::runtime_error("Failed to create font: " + std::string(SDL_GetError()));
        }
        
        current_message = N_MESSAGES - 1;

        field_size = vec2(0, 0);
        field_data = nullptr;
        field_pos = FIELD_POSITION;
        shake_time = 0;
    }

    void GUIGameRenderer::setTint(rgba32 color)
    {
        tint_color = color;
        tint_time = SDL_GetTicks64();
    }

    void GUIGameRenderer::setShake()
    {
        shake_time = SDL_GetTicks64();
    }

    void GUIGameRenderer::handle(const DoubleDamage &ability)
    {
        handle("You were blessed with double damage!!!!");
        setTint(DOUBLEDAMAGE_COLOR);
    }

    void GUIGameRenderer::handle(const SneakyAttack &ability)
    {
        handle("Sneaky attack was performed successfully!!!");
        setTint(SNEAKY_ATTACK_COLOR);
        setShake();
    }

    void GUIGameRenderer::handle(const Scanner &ability)
    {
        if (ability.isFound()) {
            handle("Found ship here!!!!");
        }
        else {
            handle("Nothing here :((((");
        }

        handle(bbox2(ability.getPosition(), ability.getPosition() + vec2(2, 2)));
        setTint(SCANNER_COLOR);
    }

    GUIGameRenderer::~GUIGameRenderer()
    {
        delete [] field_data;

        TTF_CloseFont(font);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
}
