#include "ability.hpp"
#include <iostream>

namespace seabattle {
    AbilityFactory &AbilityFactory::getInstance()
    {
        static AbilityFactory instance;
        return instance;
    }
        
    bool AbilityFactory::registerAbility(GeneratorFn generator) {
        generators.push_back(generator);
        std::cout << "Registered new ability" << std::endl;
        return true;
    }

    AbilityFactory::GeneratorFn AbilityFactory::getGenerator(size_t index)
    {
        return generators[index];
    }

    size_t AbilityFactory::getSize()
    {
        return generators.size();
    }
}
