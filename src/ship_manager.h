#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <initializer_list>
#include <list>
#include <optional>

#include "ship.h"

namespace seabattle {
    class ShipManager {
    private:
        size_t ship_size_cnt[Ship::max_size]; 
        std::list<Ship> ships;
    public:
        typedef std::list<Ship>::const_iterator Iterator;

        ShipManager(std::initializer_list<size_t> ship_size_list);
        void CreateShip(vec2 position, size_t size, Ship::Orientation orientation);

        std::optional<Ship::Iterator> operator[](vec2 position);

        inline Iterator begin() { return ships.begin(); }
        inline Iterator end()   { return ships.end(); }
    };
}

#endif
