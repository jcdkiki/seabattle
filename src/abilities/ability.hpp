#ifndef SEABATTLE_ABILITY_HPP_
#define SEABATTLE_ABILITY_HPP_

#include <functional>
#include <memory>
#include <vector>

#include "messaging/message_generator.hpp"
#include "player.hpp"

namespace seabattle {
    class Ability : public MessageGenerator {;
    public:
        virtual void use() = 0;
        virtual ~Ability() {}
    };

    class AbilityRegistry {
    public:
        using FactoryFn = std::function<std::unique_ptr<Ability>(Player &user, Player &target)>;

        struct Entry {
            const char *name;
            FactoryFn factory;
        };

        using Iterator = std::vector<Entry>::const_iterator;
    private:
        std::vector<Entry> factories;
        AbilityRegistry() = default;
    public:
        static AbilityRegistry &self();

        inline size_t count() { return factories.size(); }
        inline Iterator begin() { return factories.begin(); }
        inline Iterator end() { return factories.end(); }

        bool add(const char *name, FactoryFn factory);
    };
}

#endif
