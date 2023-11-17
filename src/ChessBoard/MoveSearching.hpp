#ifndef __MoveSearching_hpp__   
#define __MoveSearching_hpp__

#include "Board.hpp"
#include "Move.hpp"
#include <SFML/System/Clock.hpp>
#include <ctime>
#include <cmath>

class MoveSearching {
public:
    MoveSearching(int depth);
    ~MoveSearching();

    int Searching(Board& board, int timeSearchingMs, int searchDepth); //, int alpha, int beta, bool isMaximizingPlayer);
    int CalculateScore(const Board& board);
    std::vector<Move> getRankMove(int numberMoves); // get some best moves
    bool IsSearchCompleted() const;
    Move GetBestMove() const;

private:
    int searchDepth;
    int maxDepth;
    std::vector<MoveSearching*> moveSearches;
    std::vector<Move> moveSelections;
    std::vector<int> moveScore;
    std::vector<std::pair<int, Move>> moveSelectionsSorted;
    // Move selectedMove, 
    Move bestMove;
    // int selectedScore;
    int analysisPoint;
    int analysisUncompletePoint;
    int score;

    int multiplyScore;
    int cntMoves;
    int id_search;
    bool isSearch;
    bool isSearchComplete;
};

#endif