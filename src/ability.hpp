#ifndef SEABATTLE_ABILITY_HPP_
#define SEABATTLE_ABILITY_HPP_

#include <cstddef>
#include <vector>

namespace seabattle {
    class Player;

    class Ability {
    protected:
        static bool isRegistered;
    public:
        virtual void use(Player &user) = 0;
        virtual const char *getName() = 0;
        virtual ~Ability() {}
    };

    class AbilityFactory {
    public:
        typedef Ability *(*GeneratorFn)();
    private:
        std::vector<GeneratorFn> generators;
        AbilityFactory() = default;
    public:
        static AbilityFactory &getInstance();

        size_t getSize();
        GeneratorFn getGenerator(size_t index);
        bool registerAbility(GeneratorFn generator);
    };
}

#endif
