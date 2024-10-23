#ifndef SEABATTLE_MESSAGING_MESSAGE_RECIEVER_HPP_
#define SEABATTLE_MESSAGING_MESSAGE_RECIEVER_HPP_

#include <unordered_map>
#include <functional>
#include <typeindex>
#include <memory>
#include <stdexcept>

#include "messaging/message.hpp"

namespace seabattle {
class MessageReciever {
    protected:
        using HandlerMethod = void(MessageReciever::*)(std::unique_ptr<const Message>);
        std::unordered_map<std::type_index, HandlerMethod> handlers;
    
        HandlerMethod getHandlerFor(const Message &msg)
        {
            auto it = handlers.find(std::type_index(typeid(msg)));
            if (it != handlers.end()) {
                return it->second;
            }
            return nullptr;
        }

        template<class T>
        inline void registerHandler(HandlerMethod handler)
        {
            handlers.insert({ std::type_index(typeid(T)), handler });
        }

    public:
        virtual void update() {};
        virtual void handleMessage(std::unique_ptr<const Message> msg)
        {
            const Message &msg_ref = *msg;
            HandlerMethod method = getHandlerFor(msg_ref);
            if (method == nullptr) {
                throw std::runtime_error(std::string("can't find handler for message ") + typeid(msg_ref).name());
            }

            std::invoke(method, this, std::move(msg));
        }
    };
}

#endif
