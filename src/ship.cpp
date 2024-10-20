#include "ship.hpp"

#include <stdexcept>

namespace seabattle {
    Ship::Ship(size_t size) : size(size), health(size * 2)
    {
        if (size > MAX_SIZE || size == 0) {
            throw std::invalid_argument("Invalid ship size");
        }

        for (size_t i = 0; i < size; i++) {
            segments[i] = SegmentState::FULL;
        }
    }

    void Ship::damageSegment(size_t index)
    {
        SegmentState state = (*this)[index];
        SegmentState new_state;
        if (state != SegmentState::DESTROYED) {
            health--;
        }
        
        switch (state) {
            case SegmentState::FULL:
                new_state = SegmentState::DAMAGED;
                break;
            case SegmentState::DAMAGED:
                new_state = SegmentState::DESTROYED;
                break;
            case SegmentState::DESTROYED:
                new_state = SegmentState::DESTROYED;
                break;
        }

        segments[index] = new_state;
    }
}
