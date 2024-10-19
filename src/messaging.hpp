#ifndef SEABATTLE_GAME_OUTPUT_HPP_
#define SEABATTLE_GAME_OUTPUT_HPP_

#include <functional>
#include <queue>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include "messages.hpp"

namespace seabattle {
    class MessageGenerator {
    private:
        std::queue<const Message*> messages;
    
    protected:
        void pushMessage(const Message *msg)
        {
            messages.push(msg);
        }
    
    public:
        const Message *popMessage()
        {
            if (messages.size() == 0) {
                return nullptr;
            }

            const Message *msg = messages.front();
            messages.pop();
            return msg;
        }

        ~MessageGenerator()
        {
            while (messages.size() > 0) {
                delete messages.front();
                messages.pop();
            }
        }
    };

    class MessageReciever {
    protected:
        typedef bool (MessageReciever::*HandlerMethod)(const Message &msg);
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
        virtual bool handleMessage(const Message *msg)
        {
            HandlerMethod method = getHandlerFor(*msg);
            if (method == nullptr) {
                throw std::runtime_error(std::string("couldn't find handler for message ") + typeid(*msg).name());
            }

            return std::invoke(method, *this, *msg);
        }
    };

    class MessageTransformer : public MessageReciever, public MessageGenerator {};
}

#endif
