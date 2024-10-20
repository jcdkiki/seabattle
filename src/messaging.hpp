#ifndef SEABATTLE_GAME_OUTPUT_HPP_
#define SEABATTLE_GAME_OUTPUT_HPP_

#include <functional>
#include <queue>
#include <stdexcept>
#include <type_traits>
#include <typeindex>
#include <memory>
#include <unordered_map>
#include "messages.hpp"

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

    class StaticMessageReciever {
    protected:
        using HandlerMethod = void(StaticMessageReciever::*)(std::unique_ptr<const Message>);
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

    class MessageReciever : public StaticMessageReciever {
    public:
        virtual void update() {};
    };

    class MessageTransformer : public StaticMessageReciever, public StaticMessageGenerator {};

    class MessagePipe : public MessageTransformer {
    public:
        void handleMessage(std::unique_ptr<const Message> msg)
        {
            const Message &msg_ref = *msg;
            HandlerMethod method = getHandlerFor(msg_ref);
            if (method == nullptr) {
                push(std::move(msg));
                return;
            }

            std::invoke(method, this, std::move(msg));
        }
    };
}

#endif
