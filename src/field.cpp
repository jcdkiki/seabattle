#include "field.h"
#include "ship.h"
#include "ship_manager.h"
#include "colors.h"

#include <stdexcept>
#include <cstring>
#include <GL/gl.h>
#include <utility>

namespace seabattle {
    Field::Field(int width, int height) : size(width, height)
    {
        if (width < 0 || height < 0) {
            throw std::invalid_argument("invalid field size");
        }

        if (width != 0 && height != 0) {
            this->data = new State[width * height];
        }
        else {
            this->data = nullptr;
        }
    }

    Field::Field(vec2 size) : Field(size.x, size.y)
    {
        for (size_t i = 0; i < size.x * size.y; i++) {
            data[i] = State::UNKNOWN;
        }
    }

    Field::Field(const Field &field) : Field(field.size.x, field.size.y)
    {
        memcpy(this->data, field.data, sizeof(State) * size.x * size.y);
    }

    Field::Field(Field &&field) :
          data(std::exchange(field.data, nullptr)),
          size(std::exchange(field.size, vec2(0, 0)))
    {}

    Field &Field::operator=(const Field &field)
    {
        size = field.size;
        data = new State[size.x * size.y];
        memcpy(data, field.data, sizeof(State) * size.x * size.y);
        return *this;
    }

    Field &Field::operator=(Field &&field)
    {
        data = field.data;
        size = field.size;
        field.data = nullptr;
        field.size = vec2(0, 0);

        return *this;
    }

    bbox2 Field::getBoundingBox() const
    {
        return bbox2(vec2(0, 0), size);
    }

    void Field::createShip(ShipManager &ship_manager, vec2 position, size_t size, Ship::Orientation orientation, bool is_visible)
    {
        bbox2 ship_bbox = Ship::getBoundingBox(position, size, orientation);
        bbox2 field_bbox = this->getBoundingBox();

        if (!field_bbox.contains(ship_bbox)) {
            throw std::invalid_argument("Ship is located outsie the field");
        }

        ship_bbox.min -= vec2(1, 1);
        ship_bbox.max += vec2(1, 1);

        for (const Ship &ship : ship_manager) {
            if (ship.getBoundingBox().intersects(ship_bbox)) {
                throw std::invalid_argument("Ship intersects area that need to be free");
            }
        }

        ship_manager.createShip(position, size, orientation);

        if (is_visible) {
            vec2 delta = (orientation == Ship::Orientation::HORIZONTAL) ? vec2(1, 0) : vec2(0, 1);
            vec2 cur_position = position;

            for (int i = 0; i < size; i++) {
                this->at(cur_position) = State::FULL_SHIP;
                cur_position += delta;
            }
        }
    }

    void Field::render() const
    {
        glLoadIdentity();      
        glBegin(GL_TRIANGLES);
        for (size_t y = 0; y < size.y; y++) {
            for (size_t x = 0; x < size.x; x++) {
                switch (this->at(vec2(x, y))) {
                    case State::UNKNOWN:
                        glColor3ub(colors::FOG.r, colors::FOG.g, colors::FOG.b);
                        break;
                    case State::EMPTY:
                        glColor3ub(colors::WATER.r, colors::WATER.g, colors::WATER.b);
                        break;
                    case State::FULL_SHIP:
                        glColor3ub(colors::FULL.r, colors::FULL.g, colors::FULL.b);
                        break;
                    case State::DAMAGED_SHIP:
                        glColor3ub(colors::DAMAGED.r, colors::DAMAGED.g, colors::DAMAGED.b);
                        break;
                    case State::DESTROYED_SHIP:
                        glColor3ub(colors::DESTROYED.r, colors::DESTROYED.g, colors::DESTROYED.b);
                        break;
                    default:
                        glColor3ub(colors::ERROR.r, colors::ERROR.g, colors::ERROR.b);
                        break;
                }

                vec2 screen_coord = vec2(x*cell_size.x, y*cell_size.y) + field_position;
                glVertex2i(screen_coord.x, screen_coord.y);
                glVertex2i(screen_coord.x + cell_size.x, screen_coord.y);
                glVertex2i(screen_coord.x + cell_size.x, screen_coord.y + cell_size.y);
                
                glVertex2i(screen_coord.x, screen_coord.y);
                glVertex2i(screen_coord.x + cell_size.x, screen_coord.y + cell_size.y);
                glVertex2i(screen_coord.x, screen_coord.y + cell_size.y);
            }
        }
        glEnd();
    
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        for (size_t i = 0; i <= size.x; i++) {
            glVertex2i(field_position.x + i*cell_size.x, field_position.y);
            glVertex2i(field_position.x + i*cell_size.x, field_position.y + size.y*cell_size.y);
        }
        for (size_t i = 0; i <= size.y; i++) {
            glVertex2i(field_position.x, field_position.y + i*cell_size.y);
            glVertex2i(field_position.x + size.x*cell_size.x, field_position.y + i*cell_size.y);
        }
        glEnd();
    }

    void Field::coverInFog()
    {
        for (size_t i = 0; i < size.x * size.y; i++) {
            data[i] = State::UNKNOWN;
        }
    }

    Field::~Field()
    {
        if (data != nullptr)
            delete [] data;
    }

    Field::State Field::segmentStateToCellState(Ship::SegmentState state)
    {
        switch (state) {
            case Ship::SegmentState::FULL:
                return State::FULL_SHIP;
            case Ship::SegmentState::DAMAGED:
                return State::DAMAGED_SHIP;
            case Ship::SegmentState::DESTROYED:
                return State::DESTROYED_SHIP;
        }
    }

    void Field::attack(ShipManager &ship_manager, vec2 coordinates)
    {
        Ship::Iterator it = ship_manager[coordinates];
        if (it) {
            it.damage();
            this->at(coordinates) = segmentStateToCellState(*it);
            return;   
        }

        this->at(coordinates) = State::EMPTY;
    }

    Field::State &Field::at(vec2 coordinates) const
    {
        if (!this->getBoundingBox().contains(coordinates)) {
            throw std::invalid_argument("invalid coordinates");
        }
        return data[coordinates.x + coordinates.y * size.x];
    }
}
