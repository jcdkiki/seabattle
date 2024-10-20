#include "ship_manager.hpp"

namespace seabattle {
    ShipManager::ShipManager(std::initializer_list<size_t> ship_size_list)
    {
        for (size_t size : ship_size_list) {
            ships.emplace_back(size);
        }
    }
}
