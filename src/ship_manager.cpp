#include "ship_manager.h"

namespace seabattle {
    ShipManager::ShipManager(std::initializer_list<size_t> ship_size_list)
    {
        for (size_t size : ship_size_list) {
            ships.emplace_back(size);
        }
    }
}
