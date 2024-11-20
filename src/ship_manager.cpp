#include "ship_manager.hpp"

#include <ostream>
#include <istream>

namespace seabattle {
    ShipManager::ShipManager(std::initializer_list<size_t> ship_size_list)
    {
        for (size_t size : ship_size_list) {
            ships.emplace_back(size);
        }
    }

    size_t ShipManager::countActiveShips() const
    {
        size_t count = 0;
        for (const Ship &ship : ships) {
            count += !ship.isDestroyed();
        }
        return count;
    }

    std::ostream &operator<<(std::ostream &os, ShipManager &manager)
    {
        os << manager.ships.size() << '\n';       
        for (Ship &ship : manager.ships) {
            for (Ship::SegmentState segment : ship) {
                char c;
                switch (segment) {
                    case Ship::SegmentState::FULL: c = '2'; break;
                    case Ship::SegmentState::DAMAGED: c = '1'; break;
                    case Ship::SegmentState::DESTROYED: c = '0'; break;
                }

                os << c;
            }
            os << ' ';
        }
        
        return os;
    }

    std::istream &operator>>(std::istream &is, ShipManager &manager)
    {
        manager = ShipManager();
        ssize_t size;
        is >> size;

        while (size--) {
            std::string str;
            is >> str;

            Ship ship(str.size());

            for (size_t i = 0; i < str.size(); i++) {
                Ship::SegmentState state;
                switch (str[i]) {
                    case '2': state = Ship::SegmentState::FULL; break;
                    case '1': state = Ship::SegmentState::DAMAGED; break;
                    case '0': state = Ship::SegmentState::DESTROYED; break;
                }

                ship[i] = state;
            }

            manager.ships.push_back(ship);
        }

        return is;
    }
}
