#ifndef SEABATTLE_SHIP_H_
#define SEABATTLE_SHIP_H_

#include <array>
#include <cstddef>
#include <stdexcept>

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
        size_t health;
        std::array<SegmentState, MAX_SIZE> segments;

    public:
        class SegmentView {
            Ship *ship;
            size_t index;
        public:
            SegmentView(Ship *ship = nullptr, size_t index = 0) : ship(ship), index(index) {}
            void damage() const
            {
                if (ship == nullptr) {
                    throw std::runtime_error("Ship::SegmentView points to nothing");
                }
                ship->damageSegment(index);
            }

            inline SegmentState operator*() const
            {
                if (ship == nullptr) {
                    throw std::runtime_error("Ship::SegmentView points to nothing");
                }
                return ship->segments[index];
            }

            inline operator bool() const { return ship != nullptr; }

            inline Ship& getShip() const {
                if (ship == nullptr) {
                    throw std::runtime_error("Ship::SegmentView points to nothing");
                }
                return *ship;
            }

            inline size_t getIndex() const { return index; }
        };

        explicit Ship(size_t size);
        
        void damageSegment(size_t index);
        inline size_t getSize() const { return size; }
        bool isDestroyed() const { return health == 0; };
        
        SegmentState operator[](size_t index) const
        {
            if (index >= size) {
                throw std::invalid_argument("Index is too large");
            }

            return segments[index];
        }

        typedef std::array<SegmentState, MAX_SIZE>::iterator Iterator;
        inline Iterator begin() { return segments.begin(); }
        inline Iterator end()   { return segments.begin() + size; }
        inline SegmentState &operator[](size_t index) { return segments[index]; }
    };
}

#endif
