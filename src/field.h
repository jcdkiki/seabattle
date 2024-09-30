#ifndef SEABATTLE_FIELD_H_
#define SEABATTLE_FIELD_H_

#include "ship_manager.h"
#include "vec2.h"
#include <cstring>
#include <stdexcept>
#include <SFML/OpenGL.hpp>

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

        void AllocateData(vec2 size)
        {
            this->size = size;
            
            if (size.x == 0 || size.y == 0) {
                data = nullptr;
                return;
            }

            data = new State[size.x * size.y];
        }
    public:
        Field(vec2 size) : ship_manager({2, 2, 2, 1})
        {
            AllocateData(size);
            for (size_t i = 0; i < size.x * size.y; i++) {
                data[i] = UNKNOWN;
            }
        }

        Field(const Field &field) : ship_manager({2, 2, 2, 1})
        {
            this->operator=(field);
        }

        Field(Field &&field) : ship_manager({2, 2, 2, 1})
        {
            this->operator=(field);
        }

        Field &operator=(const Field &field)
        {
            AllocateData(field.size);
            memcpy(this->data, field.data, sizeof(State) * size.x * size.y);
            return *this;
        }

        Field &operator=(Field &&field)
        {
            this->size = field.size;
            data = field.data;

            field.size = vec2(0, 0);
            field.data = nullptr;
            return *this;
        }

        bbox2 GetBoundingBox() const
        {
            return bbox2(vec2(0, 0), size);
        }

        void CreateShip(vec2 position, size_t size, Ship::Orientation orientation)
        {
            bbox2 ship_bbox = Ship::GetBoundingBox(position, size, orientation);
            bbox2 field_bbox = this->GetBoundingBox();

            if (!field_bbox.intersects(ship_bbox)) {
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
        }

        void render()
        {
            glBegin(GL_TRIANGLES);
            for (size_t y = 0; y < size.y; y++) {
                for (size_t x = 0; x < size.x; x++) {
                    switch (data[x + y*size.x]) {
                        case State::UNKNOWN:
                            glColor3ub(0, 0, 0);
                            break;
                        case State::EMPTY:
                            glColor3ub(124, 124, 235);
                            break;
                        case State::FULL_SHIP:
                            glColor3ub(80, 222, 94);
                            break;
                        case State::DAMAGED_SHIP:
                            glColor3ub(222, 130, 80);
                            break;
                        case State::DESTROYED_SHIP:
                            glColor3ub(222, 80, 80);
                            break;
                    }

                    vec2 screen_coord(x*16 + 10, y*16 + 10);
                    glVertex2i(screen_coord.x, screen_coord.y);
                    glVertex2i(screen_coord.x + 16, screen_coord.y);
                    glVertex2i(screen_coord.x + 16, screen_coord.y + 16);

                    glVertex2i(screen_coord.x + 16, screen_coord.y);
                    glVertex2i(screen_coord.x + 16, screen_coord.y + 16);
                    glVertex2i(screen_coord.x, screen_coord.y);
                }
            }
            glEnd();
        }

        ~Field()
        {
            if (data != nullptr)
                delete [] data;
        }
    };
}

#endif
