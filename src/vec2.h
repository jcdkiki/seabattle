#ifndef SEABATTLE_POINT_H_
#define SEABATTLE_POINT_H_

namespace seabattle {
    struct vec2 {
        int x;
        int y;

        constexpr vec2() : x(0), y(0) {}
        constexpr vec2(int x, int y) : x(x), y(y) {}

        inline vec2 operator+(vec2 v) const { return vec2(x + v.x, y + v.y); }
        inline vec2 operator-(vec2 v) const { return vec2(x - v.x, y - v.y); }

        inline void operator+=(vec2 v) { x += v.x; y += v.y; }
        inline void operator-=(vec2 v) { x -= v.x; y -= v.y; }
    };

    struct bbox2 {
        vec2 min;
        vec2 max;

        constexpr bbox2() : min(), max() {}
        constexpr bbox2(vec2 min, vec2 max) : min(min), max(max) {}

        inline bool contains(vec2 point) const
        {
            return point.x >= min.x &&
                   point.y >= min.y &&
                   point.x <  max.x &&
                   point.y <  max.y;
        }

        inline bool contains(bbox2 bbox) const
        {
            return bbox.min.x >= min.x &&
                   bbox.min.y >= min.y &&
                   bbox.max.x <= max.x &&
                   bbox.max.y <= max.y;
        }

        inline bool intersects(bbox2 bbox) const
        {
            return (bbox.max.x > min.x) && (max.x > bbox.min.x) &&
                   (bbox.max.y > min.y) && (max.y > bbox.min.y);
        }

    };
}

#endif
