#include "ship_manager.h"

#include <stdexcept>

namespace seabattle {
    ShipManager::ShipManager(std::initializer_list<size_t> ship_size_list)
        : ship_size_cnt()
    {
        for (size_t size : ship_size_list) {
            if (size == 0 || size > Ship::MAX_SIZE) {
                throw std::invalid_argument("Invalid ship size");
            }
            ship_size_cnt[size - 1]++;
        }
    }

    void ShipManager::createShip(vec2 position, size_t size, Ship::Orientation orientation)
    {
        if (size == 0 || size > Ship::MAX_SIZE) {
            throw std::invalid_argument("Invalid ship size");
        }

        if (ship_size_cnt[size - 1] == 0) {
            throw std::invalid_argument("Maximum amount of ships this big already created");
        }

        ships.emplace_back(position, size, orientation);
        ship_size_cnt[size - 1]--;
    }

    Ship::Iterator ShipManager::operator[](vec2 position)
    {
        for (Ship &ship : ships) {
            Ship::Iterator it = ship[position];
            if (it) {
                return it;
            }
        }
        return Ship::Iterator();
    }
}
