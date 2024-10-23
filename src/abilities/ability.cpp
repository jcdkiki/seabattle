#include "ability.hpp"

namespace seabattle {
    AbilityRegistry &AbilityRegistry::self()
    {
        static AbilityRegistry instance;
        return instance;
    }
        
    bool AbilityRegistry::add(const char *name, FactoryFn factory) {
        factories.push_back({name, factory});
        return true;
    }
}
