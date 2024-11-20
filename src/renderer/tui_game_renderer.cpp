#include "tui_game_renderer.hpp"

#include <unistd.h>
#include <iostream>

namespace seabattle {
    void TUIGameRenderer::handle(std::string_view text)
    {
        std::cout << text << std::endl;
    }

    void TUIGameRenderer::handle(bbox2 cursor)
    {
        this->cursor = cursor;
    }

    void TUIGameRenderer::handle(const Field &field)
    {
        std::cout << "FIELD:" << std::endl;

        vec2 size = field.getSize();
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                if (cursor.contains(vec2(x, y))) {
                    std::cout << "\033[31;1;4m";
                }

                const Field::Cell &cell = field[vec2(x, y)];
                char c;
                if (cell.has_fog) {
                    c = '#';
                }
                else if (cell.ship_segment) {
                    switch (*cell.ship_segment) {
                        case Ship::SegmentState::FULL:      c = '$'; break;
                        case Ship::SegmentState::DAMAGED:   c = '?'; break;
                        case Ship::SegmentState::DESTROYED: c = 'X'; break;
                        default:                            c = ' '; break;
                    }
                }
                else {
                    c = '.';
                }

                std::cout << c << ' ';

                if (cursor.contains(vec2(x, y))) {
                    std::cout << "\033[0m";
                }
            }
            std::cout << std::endl;
        }
    }

    void TUIGameRenderer::handle(const DoubleDamage &ability)
    {
        handle("You were blessed with double damage!!!!");
    }

    void TUIGameRenderer::handle(const SneakyAttack &ability)
    {
        handle("Sneaky attack was performed successfully!!!");
    }

    void TUIGameRenderer::handle(const Scanner &ability)
    {
        if (ability.isFound()) {
            handle("Found ship here!!!!");
        }
        else {
            handle("Nothing here :((((");
        }

        handle(bbox2(ability.getPosition(), ability.getPosition() + vec2(2, 2)));
    }
}
