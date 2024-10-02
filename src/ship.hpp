#ifndef SEABATTLE_SHIP_H_
#define SEABATTLE_SHIP_H_

#include <cstddef>

namespace seabattle {
    class Ship {
    public:
        static constexpr size_t MAX_SIZE = 4;
        
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
        size_t size;
        SegmentState segments[MAX_SIZE];

    public:
        class Iterator {
            Ship *ship;
            size_t index;
        public:
            Iterator(Ship *ship = nullptr, size_t index = 0) : ship(ship), index(index) {}
            void damage() { ship->damageSegment(index); }

            inline SegmentState operator*() { return ship->segments[index]; }
            inline operator bool() { return ship != nullptr; }
        };

        explicit Ship(size_t size);
        
        void damageSegment(size_t index);
        inline size_t getSize() const { return size; }
    };
}

#endif
