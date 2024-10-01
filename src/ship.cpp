#include "ship.h"

#include <stdexcept>

namespace seabattle {
    Ship::Ship(vec2 position, size_t size, Orientation orientation)
        : position(position), size(size), orientation(orientation)
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
        if (index >= size) {
            throw std::invalid_argument("Index is too large");
        }

        SegmentState new_state;
        switch (segments[index]) {
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

    Ship::Iterator Ship::operator[](vec2 position)
    {
        if (!this->getBoundingBox().contains(position)) {
            return Iterator(nullptr, 0);
        }
        
        size_t index;
        if (orientation == Orientation::HORIZONTAL)
            index = position.x - this->position.x;
        else
            index = position.y - this->position.y;
        
        return Iterator(this, index);
    }
}
