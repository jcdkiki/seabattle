#ifndef ABILITY_REGISTRY_H
#define ABILITY_REGISTRY_H

#include <functional>
#include <map>
#include "ability.hpp"

namespace seabattle {
    class Player;
    class GameRenderer;

    class AbilityRegistry {
    public:
        using GeneratorFn = std::function<Ability*(Player &user, Player &target)>;
        using RenderFn    = std::function<void(GameRenderer& renderer, const Ability &ability)>;

        struct AbilityInfo {
            GeneratorFn generator;
            RenderFn render;

            AbilityInfo(GeneratorFn generator, RenderFn render) :
                generator(generator), render(render)
            {}
        };

        using Entry = std::map<const char*, AbilityInfo>::const_iterator;
    private:
        std::map<const char*, AbilityInfo> entries;
        AbilityRegistry() = default;
    public:
        static AbilityRegistry &self();

        inline size_t count() { return entries.size(); }
        inline Entry begin() { return entries.cbegin(); }
        inline Entry end() { return entries.cend(); }

        bool add(const char *name, AbilityInfo info);
    };
}

#endif // ABILITY_REGISTRY_H
