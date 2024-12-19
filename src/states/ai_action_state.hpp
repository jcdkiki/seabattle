#ifndef SEABATTLE_AI_ACTION_STATE_HPP_
#define SEABATTLE_AI_ACTION_STATE_HPP_

#include "game_state.hpp"

namespace seabattle {
    class AIActionState : public GameState {
    public:
        static constexpr const char *name = "AIAction";

        void primaryAction();
        
        AIActionState(Game &game);
        std::string_view getName() const;
    };
}

#endif
