#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <list>

#include "ship.hpp"

namespace seabattle {
    class ShipManager {
    private:
        std::list<Ship> ships;

    public:
        typedef std::list<Ship>::iterator Iterator;

        ShipManager(std::initializer_list<size_t> ship_size_list = {3, 3});
        
        inline Iterator begin() { return ships.begin(); }
        inline Iterator end()   { return ships.end(); }
    };
}

#endif
