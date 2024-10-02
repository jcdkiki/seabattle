#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <list>

#include "ship.h"

namespace seabattle {
    class ShipManager {
    private:
        std::list<Ship> ships;

    public:
        typedef std::list<Ship>::iterator Iterator;

        ShipManager(std::initializer_list<size_t> ship_size_list = {1, 1, 1, 2, 2, 3, 3, 4});
        
        inline Iterator begin() { return ships.begin(); }
        inline Iterator end()   { return ships.end(); }
    };
}

#endif
