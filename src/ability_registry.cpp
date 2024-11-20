#include "ability_registry.hpp"

namespace seabattle {
    AbilityRegistry &AbilityRegistry::self()
    {
        static AbilityRegistry instance;
        return instance;
    }
}
