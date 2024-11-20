#ifndef SEABATTLE_SHIP_MANAGER_H_
#define SEABATTLE_SHIP_MANAGER_H_

#include <initializer_list>
#include <stdexcept>
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
            if (begin == end) {
                throw std::invalid_argument("No ships were created");
            }

            while (begin != end) {
                ships.emplace_back(*begin);
                begin++;
            }
        }
        
        size_t countActiveShips() const;

        inline size_t count() { return ships.size(); }
        inline Iterator begin() { return ships.begin(); }
        inline Iterator end()   { return ships.end(); }

        friend std::ostream &operator<<(std::ostream &os, ShipManager &manager);
        friend std::istream &operator>>(std::istream &is, ShipManager &manager);
    };
}

#endif
