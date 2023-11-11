#ifndef __Bot_hpp__
#define __Bot_hpp__

#include "NewBoard.hpp"
#include "MoveSearching.hpp"
#include <SFML/System/Clock.hpp>

class Bot {
public:
    Bot();
    ~Bot();

private:
    NewBoard* board;
    const int limitThinkingTimeMs = 30;
    int searchDepth;
    int timeThinkingMs;

    int currentTimeThinkingMs;
    std::vector<Move> moveSelections;
    std::vector<std::pair<Move, int>> moveScores;
    Move bestMove;
    MoveSearching* moveSearching;

    bool isThinkingDone;
    int timeRemainMs;
    sf::Clock clock;
    
public:
    void LoadBoard(const NewBoard& board);
    void LoadFEN(std::string fen);
    void setSearchDepth(int searchDepth);
    void setTimeThinkingMs(double timeThinkingMs);
    void Thinking();

    bool ifThinkingDone();
    Move getBestMove();
};

#endif