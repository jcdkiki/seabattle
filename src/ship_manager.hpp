#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <initializer_list>
#include <vector>

#include "ship.hpp"

namespace seabattle {
    class ShipManager {
    private:
        std::vector<Ship> ships;

    public:
        using Iterator = std::vector<Ship>::iterator;

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
