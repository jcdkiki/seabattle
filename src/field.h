#ifndef SEABATTLE_FIELD_H_
#define SEABATTLE_FIELD_H_

#include "vec2.h"
#include "ship_manager.h"
#include "ship.h"

namespace seabattle {
    class Field {
        enum State : char {
            UNKNOWN,
            EMPTY,
            FULL_SHIP,
            DAMAGED_SHIP,
            DESTROYED_SHIP
        };

        State *data;
        vec2 size;
        ShipManager ship_manager;

        Field();
        void CreateJunk(vec2 size);
        static Field::State SegmentStateToCellState(Ship::SegmentState state);

        State &At(vec2 coordinates) const;

    public:
        static constexpr vec2 cell_size{16, 16};
        static constexpr vec2 field_position{10, 70};

        Field(vec2 size);
        Field(const Field &field);
        Field(Field &&field);
        ~Field();
        Field &operator=(const Field &field);
        Field &operator=(Field &&field);
        
        bbox2 GetBoundingBox() const;

        void Attack(vec2 coordinates);
        void CreateShip(vec2 position, size_t size, Ship::Orientation orientation, bool is_visible = false);
        void Render() const;
        void CoverInFog();
        int GetNumberOfAvailibleShips(size_t size) const;
    };
}

#endif
