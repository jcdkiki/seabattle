#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <initializer_list>
#include <list>

#include "ship.hpp"

namespace seabattle {
    class ShipManager {
    private:
        std::list<Ship> ships;

    public:
        typedef std::list<Ship>::iterator Iterator;

        ShipManager(std::initializer_list<size_t> ship_size_list = {});
        
        template<class Iterable>
        ShipManager(Iterable begin, Iterable end)
        {
            while (begin != end) {
                ships.emplace_back(*begin);
                begin++;
            }
        }
        
        inline Iterator begin() { return ships.begin(); }
        inline Iterator end()   { return ships.end(); }
    };
}

#endif
