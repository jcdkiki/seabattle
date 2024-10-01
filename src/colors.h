#ifndef SEABATTLE_COLORS_H_
#define SEABATTLE_COLORS_H_

#include <SFML/Graphics/Color.hpp>

namespace seabattle {
    struct Color {
        unsigned char r, g, b;
        inline operator sf::Color() const { return sf::Color(r, g, b, 255); }
    };

    namespace colors {
        constexpr Color Water { 166, 204, 237 };
        constexpr Color Full { 173, 247, 183 };
        constexpr Color Damaged { 224, 138, 76 };
        constexpr Color Destroyed { 222, 42, 42 };
        constexpr Color Fog { 78, 99, 107 };
        constexpr Color Error { 252, 0, 219 };
    };
};

#endif
