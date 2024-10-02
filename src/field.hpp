#ifndef SEABATTLE_FIELD_H_
#define SEABATTLE_FIELD_H_

#include <vector>

#include "vec2.hpp"
#include "ship.hpp"

namespace seabattle {
    class Field {
        enum State : char {
            UNKNOWN,
            EMPTY,
            FULL_SHIP,
            DAMAGED_SHIP,
            DESTROYED_SHIP
        };

        struct Entry {
            vec2 position;
            Ship::Orientation orientation;
            Ship &ship;

            inline void operator=(const Entry &entry)
            {
                position = entry.position;
                orientation = entry.orientation;
                ship = entry.ship;
            }
        };

        std::vector<Entry> ships;
        State *data;
        vec2 size;

        static Field::State segmentStateToCellState(Ship::SegmentState state);
        static bbox2 getShipBoundingBox(const Ship &ship, vec2 position, Ship::Orientation orientation);

        State &getCellState(vec2 coordinates) const;
        Ship::Iterator getShipIterator(vec2 coordinates);
        Field(int width, int height);
        
    public:
        static constexpr vec2 cell_size{16, 16};
        static constexpr vec2 field_position{10, 70};

        Field(vec2 size);
        Field(const Field &field);
        Field(Field &&field);
        ~Field();
        Field &operator=(const Field &field);
        Field &operator=(Field &&field);
        
        bbox2 getBoundingBox() const;

        void attack(vec2 coordinates);
        void addShip(Ship &ship, vec2 position, Ship::Orientation orientation, bool is_visible = false);
        void render() const;
        void coverInFog();
    };
}

#endif
