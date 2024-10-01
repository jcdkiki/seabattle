#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <list>

#include "ship.h"

namespace seabattle {
    class ShipManager {
    private:
        size_t ship_size_cnt[Ship::MAX_SIZE]; 
        std::list<Ship> ships;
    public:
        typedef std::list<Ship>::iterator Iterator;

        ShipManager(std::initializer_list<size_t> ship_size_list = {1, 1, 1, 2, 2, 3, 3, 4});
        void createShip(vec2 position, size_t size, Ship::Orientation orientation);

        Ship::Iterator operator[](vec2 position);

        inline Iterator begin() { return ships.begin(); }
        inline Iterator end()   { return ships.end(); }
        inline int getAvailibleShipsCount(size_t size) const { return ship_size_cnt[size - 1]; }
    };
}

#endif
