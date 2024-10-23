#ifndef SEABATTLE_EXCEPTION_HPP_
#define SEABATTLE_EXCEPTION_HPP_

#include <exception>

namespace seabattle {
    class SeabattleException : std::exception {
    public:
        virtual const char *what() = 0;
    };
}

#endif
