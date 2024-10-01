#include "field.h"
#include "ship.h"
#include "ship_manager.h"
#include "colors.h"

#include <stdexcept>
#include <cstring>
#include <GL/gl.h>
#include <utility>

namespace seabattle {
    void Field::CreateJunk(vec2 size)
    {
        if (size.x < 0 || size.y < 0) {
            throw std::invalid_argument("invalid field size");
        }

        if (size.x == 0 || size.y == 0) {
            this->data = nullptr;
        } else {
            this->data = new State[size.x * size.y];
        }

        this->size = size;
    }

    Field::Field(vec2 size) : ship_manager()
    {
        this->CreateJunk(size);
        for (size_t i = 0; i < size.x * size.y; i++) {
            data[i] = State::UNKNOWN;
        }
    }

    Field &Field::operator=(const Field &field)
    {
        this->CreateJunk(size);
        ship_manager = ShipManager();
        memcpy(this->data, field.data, sizeof(State) * size.x * size.y);
        return *this;
    }

    Field &Field::operator=(Field &&field)
    {
        data = field.data;
        size = field.size;
        ship_manager = field.ship_manager;

        field.data = nullptr;
        field.size = vec2(0, 0);
        field.ship_manager = ShipManager();

        return *this;
    }

    Field::Field(const Field &field) : Field(field.size)
    {
        memcpy(this->data, field.data, sizeof(State) * size.x * size.y);
    }

    Field::Field(Field &&field)
        : ship_manager(std::move(field.ship_manager)),
          data(std::exchange(field.data, nullptr)),
          size(std::exchange(field.size, vec2(0, 0)))
    {}

    bbox2 Field::GetBoundingBox() const
    {
        return bbox2(vec2(0, 0), size);
    }

    void Field::CreateShip(vec2 position, size_t size, Ship::Orientation orientation, bool is_visible)
    {
        bbox2 ship_bbox = Ship::GetBoundingBox(position, size, orientation);
        bbox2 field_bbox = this->GetBoundingBox();

        if (!field_bbox.contains(ship_bbox)) {
            throw std::invalid_argument("Ship is located outsie the field");
        }

        ship_bbox.min -= vec2(1, 1);
        ship_bbox.max += vec2(1, 1);

        for (const Ship &ship : ship_manager) {
            if (ship.GetBoundingBox().intersects(ship_bbox)) {
                throw std::invalid_argument("Ship intersects area that need to be free");
            }
        }

        ship_manager.CreateShip(position, size, orientation);

        if (is_visible) {
            vec2 delta = (orientation == Ship::Orientation::HORIZONTAL) ? vec2(1, 0) : vec2(0, 1);
            vec2 cur_position = position;

            for (int i = 0; i < size; i++) {
                this->At(cur_position) = State::FULL_SHIP;
                cur_position += delta;
            }
        }
    }

    void Field::Render() const
    {
        glLoadIdentity();      
        glBegin(GL_TRIANGLES);
        for (size_t y = 0; y < size.y; y++) {
            for (size_t x = 0; x < size.x; x++) {
                switch (this->At(vec2(x, y))) {
                    case State::UNKNOWN:
                        glColor3ub(colors::Fog.r, colors::Fog.g, colors::Fog.b);
                        break;
                    case State::EMPTY:
                        glColor3ub(colors::Water.r, colors::Water.g, colors::Water.b);
                        break;
                    case State::FULL_SHIP:
                        glColor3ub(colors::Full.r, colors::Full.g, colors::Full.b);
                        break;
                    case State::DAMAGED_SHIP:
                        glColor3ub(colors::Damaged.r, colors::Damaged.g, colors::Damaged.b);
                        break;
                    case State::DESTROYED_SHIP:
                        glColor3ub(colors::Destroyed.r, colors::Destroyed.g, colors::Destroyed.b);
                        break;
                    default:
                        glColor3ub(colors::Error.r, colors::Error.g, colors::Error.b);
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

    void Field::CoverInFog()
    {
        for (size_t i = 0; i < size.x * size.y; i++) {
            data[i] = State::UNKNOWN;
        }
    }

    int Field::GetNumberOfAvailibleShips(size_t size) const
    {
        return ship_manager.GetNumberOfAvailibleShips(size);
    }

    Field::~Field()
    {
        if (data != nullptr)
            delete [] data;
    }

    Field::State Field::SegmentStateToCellState(Ship::SegmentState state)
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

    void Field::Attack(vec2 coordinates)
    {
        Ship::Iterator it = ship_manager[coordinates];
        if (it) {
            it.Damage();
            this->At(coordinates) = SegmentStateToCellState(*it);
            return;   
        }

        this->At(coordinates) = State::EMPTY;
    }

    Field::State &Field::At(vec2 coordinates) const
    {
        if (!this->GetBoundingBox().contains(coordinates)) {
            throw std::invalid_argument("invalid coordinates");
        }
        return data[coordinates.x + coordinates.y * size.x];
    }
}
