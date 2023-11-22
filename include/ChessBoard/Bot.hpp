#ifndef __Bot_hpp__
#define __Bot_hpp__

#include <ChessBoard/Board.hpp>
#include <ChessBoard/MoveSearching.hpp>
#include <SFML/System/Clock.hpp>
#include <thread>

class Bot {
public:
    Bot();
    ~Bot();

private:
    Board* board;
    std::shared_ptr<bool> stopflag;
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
    std::thread thinkingThread;

public:
    void LoadBoard(const Board& board);
    void LoadFEN(std::string fen);
    void setSearchDepth(int searchDepth);
    void setTimeThinkingMs(double timeThinkingMs);
    void Thinking();
    void StopThinking();

    // Accessors
    std::vector<Move> getRankMove(int numberMoves);
    bool ifThinkingDone();
    Move getBestMove();
};

#endif