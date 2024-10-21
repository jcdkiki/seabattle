#ifndef SEABATTLE_MESSAGING_MESSAGE_HPP_
#define SEABATTLE_MESSAGING_MESSAGE_HPP_

#include <memory>

namespace seabattle {
    struct Message {
        virtual std::unique_ptr<Message> clone() const = 0;
        virtual ~Message() {}
    };
}

#endif
