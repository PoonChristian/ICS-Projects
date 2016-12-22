#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include <vector>
#include <algorithm>

#include "OthelloAI.hpp"

namespace ctpoon
{
    class CTPoonOthelloAI : public OthelloAI
    {
    public:
        int evaluate(OthelloGameState& state, OthelloCell originalPlayer);
        int search(OthelloGameState& state, int depth, OthelloCell originalPlayer);
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
    };
}

#endif // MYOTHELLOAI_HPP
