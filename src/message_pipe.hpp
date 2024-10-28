#ifndef MESSAGE_PIPE_H
#define MESSAGE_PIPE_H

namespace seabattle {
    template<class Parent>
    class MessagePipe {
        Parent &parent;
    public:
        MessagePipe(Parent &parent) : parent(parent) {}

        template<class Message>
        void operator<<(const Message &message)
        {
            parent << message;
        }
    };
};

#endif
