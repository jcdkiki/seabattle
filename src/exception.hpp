#ifndef SEABATTLE_EXCEPTION_HPP_
#define SEABATTLE_EXCEPTION_HPP_

namespace seabattle {
    class SeabattleException {
    public:
        virtual const char *what() = 0;
    };
}

#endif
