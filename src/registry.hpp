#ifndef SEABATTLE_REGISTRY_H
#define SEABATTLE_REGISTRY_H

#include <map>
#include <string_view>

namespace seabattle {
    template<class GeneratorFn>
    class Registry {
    public:
        struct Info {
            GeneratorFn generator;

            Info(GeneratorFn generator) : generator(generator) {}
        };

        using Entry = typename std::map<std::string_view, Info>::const_iterator;
    private:
        std::map<std::string_view, Info> entries;
    public:
        inline size_t count() { return entries.size(); }
        inline Entry begin() { return entries.cbegin(); }
        inline Entry end() { return entries.cend(); }
        inline Entry find(std::string_view name) { return entries.find(name); }

        bool add(const char *name, Info info) {
            entries.insert({ name, info });
            return true;
        }
    };
}

#endif
