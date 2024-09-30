#ifndef SEABATTLE_SHIP_H_
#define SEABATTLE_SHIP_H_

#include <optional>

#include "vec2.h"

namespace seabattle {
    class Ship {
    public:
        static constexpr size_t max_size = 4;
        
        enum class Orientation : char {
            HORIZONTAL,
            VERTICAL
        };

        enum class SegmentState : char {
            FULL = 0,
            DAMAGED,
            DESTROYED
        };

    private:
        vec2 position;
        size_t size;
        SegmentState segments[max_size];
        Orientation orientation;

    public:
        class Iterator {
            Ship &ship;
            size_t index;
        public:
            Iterator(Ship &ship, size_t index) : ship(ship), index(index) {}
            void Damage() { ship.DamageSegment(index); }
        };

        explicit Ship(vec2 position, size_t size, Orientation orientation);
        
        void DamageSegment(size_t index);
        //SegmentState GetSegmentState(size_t index) const;
        std::optional<Iterator> operator[](vec2 position);
        
        inline bbox2 GetBoundingBox() const
        {
            return Ship::GetBoundingBox(position, size, orientation);
        }

        inline static bbox2 GetBoundingBox(vec2 position, size_t size, Orientation orientation)
        {
            if (orientation == Orientation::HORIZONTAL)
                return bbox2(position, position + vec2(size, 1));
            return bbox2(position, position + vec2(1, size));
        }
    };
}

#endif
