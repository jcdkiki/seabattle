#ifndef SEABATTLE_MESSAGING_MESSAGE_PIPE_HPP_
#define SEABATTLE_MESSAGING_MESSAGE_PIPE_HPP_

#include "message_transformer.hpp"

namespace seabattle {
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
