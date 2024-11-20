#include "state_registry.hpp"

namespace seabattle {
    StateRegistry &StateRegistry::self()
    {
        static StateRegistry instance;
        return instance;
    }
}
