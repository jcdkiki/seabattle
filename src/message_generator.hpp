#ifndef MESSAGE_GENERATOR_H
#define MESSAGE_GENERATOR_H

namespace seabattle {
    template<class Parent>
    class MessageGenerator {
    protected:
        Parent &parent;
    public:
        MessageGenerator(Parent &parent) : parent(parent) {}
    };
};

#endif
