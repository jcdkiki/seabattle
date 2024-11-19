#ifndef SEABATTLE_RGBA32_HPP_
#define SEABATTLE_RGBA32_HPP_

namespace seabattle {
    struct rgba32 {
        unsigned char r, g, b, a;
        constexpr rgba32(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255)
            : r(r), g(g), b(b), a(a)
        {}
    };
};

#endif
