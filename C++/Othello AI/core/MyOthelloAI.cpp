#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, ctpoon::CTPoonOthelloAI, "Poon's AI (Required)");

namespace
{
    std::vector<std::pair<int, int>> validMoves(const OthelloGameState& state)
    {
        std::vector<std::pair<int, int>> moves;
        for (int i = 0; i < state.board().width(); ++i)
        {
            for (int j = 0; j < state.board().height(); ++j)
            {
                if (state.isValidMove(i, j) && state.board().isValidCell(i, j))
                {
                    moves.push_back(std::make_pair(i, j));
                }
            }
        }
        return moves;
    }
}


int ctpoon::CTPoonOthelloAI::evaluate(OthelloGameState& state, OthelloCell originalPlayer)
{
    int sides = 0;
    int corners = 0;
    for (int i = 0; i < state.board().width(); ++i)
    {
        for (int j = 0; j < state.board().height(); ++j)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == state.board().height() - 1) || 
                (i == state.board().width() - 1 && j == 0) || (i == state.board().width() - 1 && j == state.board().height() - 1))
            {
                if (state.board().cellAt(i, j) == originalPlayer)
                {
                    corners += 1;
                }
            }
            else if (i == 0 || j == 0 || i == state.board().width() - 1|| j == state.board().height())
            {
                if (state.board().cellAt(i, j) == originalPlayer)
                {
                    sides += 1;
                }
            }
        }
    }
    if (originalPlayer == OthelloCell::black)
    {
        return state.blackScore() - state.whiteScore() + 5*sides + 10*corners;
    }
    else
    {
        return state.whiteScore() - state.blackScore() + 5*sides + 10*corners;
    }
}


int ctpoon::CTPoonOthelloAI::search(OthelloGameState& state, int depth, OthelloCell originalPlayer)
{
    OthelloCell currentPlayer;
    if (state.isBlackTurn())
    {
        currentPlayer = OthelloCell::black;
    }
    else
    {
        currentPlayer = OthelloCell::white;
    }

    if (depth == 0 || state.isGameOver())
    {
        return evaluate(state, originalPlayer);
    }
    else
    {
        std::vector<std::pair<int, int>> legalMoves = validMoves(state);
        // If it's my turn to move
        if (currentPlayer == originalPlayer)
        {
            int max = -1000000;
            for (int i = 0; i != legalMoves.size(); ++i)
            {
                std::unique_ptr<OthelloGameState> newState = state.clone();
                newState->makeMove(legalMoves[i].first, legalMoves[i].second);
                int value = search(*newState, depth - 1, currentPlayer);
                
                if (value > max)
                    max = value;
            }

            return max;
        }
        // If it's the opponent's turn to move
        else
        {
            int min = 1000000;
            for (int i = 0; i != legalMoves.size(); ++i)
            {
                std::unique_ptr<OthelloGameState> newState = state.clone();
                newState->makeMove(legalMoves[i].first, legalMoves[i].second);
                int value = search(*newState, depth - 1, currentPlayer); 
                if (value < min)
                    min = value;
            }

            return min;
        }
    }
}

std::pair<int, int> ctpoon::CTPoonOthelloAI::chooseMove(const OthelloGameState& state)
{
    int x = 0;
    int y = 0;
    int bestValue = -1000000;
    OthelloCell aiPlayer;

    if (state.isBlackTurn())
    {
        aiPlayer = OthelloCell::black;
    }
    else
    {
        aiPlayer = OthelloCell::white;
    }

    std::vector<std::pair<int,int>> legalMoves = validMoves(state);

    for (int i = 0; i != legalMoves.size(); ++i)
    {
        std::unique_ptr<OthelloGameState> newState = state.clone();
        newState->makeMove(legalMoves[i].first, legalMoves[i].second);
        int heuristicValue = search(*newState, 3, aiPlayer);

        if (heuristicValue > bestValue)
        {
            bestValue = heuristicValue;
            x = legalMoves[i].first;
            y = legalMoves[i].second;
        }
    }
    
    return std::make_pair(x, y);
}
