#include "ability_registry.hpp"

namespace seabattle {
    AbilityRegistry &AbilityRegistry::self()
    {
        static AbilityRegistry instance;
        return instance;
    }
        
    bool AbilityRegistry::add(const char *name, AbilityInfo info) {
        entries.insert({ name, info });
        return true;
    }
}
