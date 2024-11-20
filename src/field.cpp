#include "field.hpp"
#include "ship.hpp"

#include <stdexcept>
#include <cstring>
#include <utility>

namespace seabattle {
    Field::Field(int width, int height)
        : size(width, height)
    {
        if (width < 0 || height < 0) {
            throw std::invalid_argument("Invalid field size");
        }

        if (width != 0 && height != 0) {
            this->data = new Cell[width * height];
        }
        else {
            this->data = nullptr;
        }
    }

    Field::Field(vec2 size) : Field(size.x, size.y)
    {
        for (size_t i = 0; i < size.x * size.y; i++) {
            data[i].has_fog = true;
            data[i].ship_segment = Ship::SegmentView();
        }
    }

    Field::Field(const Field &field) : Field(field.size.x, field.size.y)
    {
        memcpy(data, field.data, sizeof(*data) * size.x * size.y);
    }

    Field::Field(Field &&field) :
          data(std::exchange(field.data, nullptr)),
          size(std::exchange(field.size, vec2(0, 0)))
    {}

    Field &Field::operator=(const Field &field)
    {
        if (data) {
            delete [] data;
        }

        size = field.size;
        data = new Cell[size.x * size.y];
        memcpy(data, field.data, sizeof(*data) * size.x * size.y);
        return *this;
    }

    Field &Field::operator=(Field &&field)
    {
        if (data) {
            delete [] data;
        }

        data = field.data;
        size = field.size;
        field.data = nullptr;
        field.size = vec2(0, 0);

        return *this;
    }

    bbox2 Field::getShipBoundingBox(Ship &ship, vec2 position, Ship::Orientation orientation)
    {
        vec2 size = (orientation == Ship::Orientation::HORIZONTAL) ? vec2(ship.getSize(), 1) : vec2(1, ship.getSize());
        return bbox2(position, position + size);
    }

    void Field::addShip(Ship &ship, vec2 position, Ship::Orientation orientation, bool is_visible)
    {
        bbox2 ship_bbox = getShipBoundingBox(ship, position, orientation);
        bbox2 field_bbox = getBoundingBox();

        if (!field_bbox.contains(ship_bbox)) {
            throw IllegalShipPositionException();
        }

        ship_bbox.min -= vec2(1, 1);
        ship_bbox.max += vec2(1, 1);
        
        ship_bbox = ship_bbox.intersection(field_bbox);

        for (int y = ship_bbox.min.y; y < ship_bbox.max.y; y++) {
            for (int x = ship_bbox.min.x; x < ship_bbox.max.x; x++) {
                if (getCell(vec2(x, y)).ship_segment) {
                    throw IllegalShipPositionException();
                }
            }
        }

        vec2 delta = (orientation == Ship::Orientation::HORIZONTAL) ? vec2(1, 0) : vec2(0, 1);
        vec2 cur_position = position;

        for (int i = 0; i < ship.getSize(); i++) {
            this->getCell(cur_position).ship_segment = Ship::SegmentView(&ship, i);
            if (is_visible)
                this->getCell(cur_position).has_fog = false;
            
            cur_position += delta;
        }
    }

    void Field::coverInFog()
    {
        for (size_t i = 0; i < size.x * size.y; i++) {
            data[i].has_fog = true;
        }
    }

    Field::~Field()
    {
        if (data != nullptr)
            delete [] data;
    }

    Field::AttackResult Field::attack(vec2 coordinates, bool hidden)
    {
        Cell &cell = getCell(coordinates);
        if (!hidden) {
            cell.has_fog = false;
        }

        if (!cell.ship_segment) {
            return AttackResult::NOTHING;
        }

        cell.ship_segment.damage();

        if (cell.ship_segment.getShip().isDestroyed()) {
            return AttackResult::SHIP_DESTROYED;
        }
        return AttackResult::SHIP_DAMAGED;
    }

    Field::Cell &Field::getCell(vec2 coordinates)
    {
        if (!this->getBoundingBox().contains(coordinates)) {
            throw IllegalCoordinatesException();
        }
        return data[coordinates.x + coordinates.y * size.x];
    }

    Field::Cell &Field::operator[](vec2 coordinates)
    {
        if (!this->getBoundingBox().contains(coordinates)) {
            throw IllegalCoordinatesException();
        }
        return data[coordinates.x + coordinates.y * size.x];
    }

    const Field::Cell &Field::operator[](vec2 coordinates) const
    {
        if (!this->getBoundingBox().contains(coordinates)) {
            throw IllegalCoordinatesException();
        }
        return data[coordinates.x + coordinates.y * size.x]; 
    }

    void Field::mark(vec2 position)
    {
        if (!getBoundingBox().contains(position)) {
            return;
        }
        getCell(position).marked = !getCell(position).marked;
    }

    std::ostream &operator<<(std::ostream &os, Field &manager)
    {
        return os;
    }

    std::istream &operator>>(std::istream &is, Field &manager)
    {
        return is;
    }
}
