#ifndef SEABATTLE_FIELD_H_
#define SEABATTLE_FIELD_H_

#include <vector>

#include "vec2.hpp"
#include "ship.hpp"

namespace seabattle {
    class Field {
    public:
        struct Cell {
            Ship::SegmentView ship_segment;
            bool has_fog;
        };
    private:
        Cell *data;
        vec2 size;

        static bbox2 getShipBoundingBox(Ship &ship, vec2 position, Ship::Orientation orientation);
        Cell &getCell(vec2 coordinates);
        
        Field(int width, int height);
    public:
        static constexpr vec2 CELL_SIZE{32, 32};

        Field(vec2 size);
        Field(const Field &field);
        Field(Field &&field);
        ~Field();
        Field &operator=(const Field &field);
        Field &operator=(Field &&field);
        
        bool attack(vec2 coordinates, bool hidden);
        void addShip(Ship &ship, vec2 position, Ship::Orientation orientation, bool is_visible = false);
        void coverInFog();

        inline bbox2 getBoundingBox() const { return bbox2(vec2(0, 0), size);  }
        inline vec2 getSize() const { return size; }
        const Cell &operator[](vec2 coordinates) const;

        static vec2 worldToScreenCoord(vec2 coordinates);
    };
}

#endif
