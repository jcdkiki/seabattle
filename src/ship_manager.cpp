#include "ship_manager.h"
#include <optional>
#include <stdexcept>

namespace seabattle {
    ShipManager::ShipManager(std::initializer_list<size_t> ship_size_list)
    {
        for (size_t size : ship_size_list) {
            if (size == 0 || size > Ship::max_size) {
                throw std::invalid_argument("Invalid ship size");
            }
            ship_size_cnt[size - 1]++;
        }
    }

    void ShipManager::CreateShip(vec2 position, size_t size, Ship::Orientation orientation)
    {
        if (size == 0 || size > Ship::max_size) {
            throw std::invalid_argument("Invalid ship size");
        }

        if (ship_size_cnt[size - 1] == 0) {
            throw std::invalid_argument("Maximum amount of ships this big already created");
        }

        ship_size_cnt[size - 1]--;
        ships.emplace_back(position, size, orientation);
    }

    std::optional<Ship::Iterator> ShipManager::operator[](vec2 position)
    {
        for (Ship &ship : ships) {
            std::optional<Ship::Iterator> it = ship[position];
            if (it) {
                return it;
            }
        }
        return std::nullopt;
    }
}
