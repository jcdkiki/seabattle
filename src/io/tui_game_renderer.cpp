#include "tui_game_renderer.hpp"

#include <unistd.h>
#include <iostream>

namespace seabattle {
    void TUIGameRenderer::operator<<(std::string_view text)
    {
        std::cout << text << std::endl;
    }

    void TUIGameRenderer::operator<<(bbox2 cursor)
    {
        this->cursor = cursor;
    }

    void TUIGameRenderer::operator<<(const Field &field)
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

    void TUIGameRenderer::operator<<(const DoubleDamage &ability)
    {
        (*this) << "You were blessed with double damage!!!!";
    }

    void TUIGameRenderer::operator<<(const SneakyAttack &ability)
    {
        (*this) << "Sneaky attack was performed successfully!!!";
    }

    void TUIGameRenderer::operator<<(const Scanner &ability)
    {
        if (ability.isFound()) {
            (*this) << "Found ship here!!!!";
        }
        else {
            (*this) << "Nothing here :((((";
        }

        (*this) << bbox2(ability.getPosition(), ability.getPosition() + vec2(2, 2));
    }
}
