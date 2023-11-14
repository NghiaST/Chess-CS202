#ifndef __Bot_hpp__
#define __Bot_hpp__

#include "Board.hpp"
#include "MoveSearching.hpp"
#include <SFML/System/Clock.hpp>

class Bot {
public:
    Bot();
    ~Bot();

private:
    Board* board;
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
    void LoadBoard(const Board& board);
    void LoadFEN(std::string fen);
    void setSearchDepth(int searchDepth);
    void setTimeThinkingMs(double timeThinkingMs);
    void Thinking();

    // Accessors
    std::vector<Move> getRankMove(int numberMoves);
    bool ifThinkingDone();
    Move getBestMove();
};

#endif