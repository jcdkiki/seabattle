#ifndef SEABATTLE_MESSAGING_MESSAGE_GENERATOR_HPP_
#define SEABATTLE_MESSAGING_MESSAGE_GENERATOR_HPP_

#include <queue>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include "message.hpp"

namespace seabattle {
    class StaticMessageGenerator {
    private:
        std::queue<std::unique_ptr<const Message>> messages;
    
    protected:
        template<class MessageType, typename... Args>
        inline void emplace(Args &&...args)
        {
            static_assert(std::is_base_of_v<Message, MessageType>);
            messages.emplace(std::make_unique<MessageType>(args...));
        }

        inline void push(std::unique_ptr<const Message> msg)
        {
            messages.push(std::move(msg));
        }
    
    public:
        bool empty()
        {
            return messages.size() == 0;
        }

        std::unique_ptr<const Message> pop()
        {
            if (messages.size() == 0) {
                throw std::runtime_error("No message to pop");
            }

            std::unique_ptr<const Message> msg = std::move(messages.front());
            messages.pop();
            return std::move(msg);
        }
    };

    class MessageGenerator : public StaticMessageGenerator {
    public:
        virtual void update() {};
    };
}

#endif
