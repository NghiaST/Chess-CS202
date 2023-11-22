#ifndef __MoveSearching_hpp__   
#define __MoveSearching_hpp__

#include <ChessBoard/Board.hpp>
#include <ChessBoard/Move.hpp>
#include <SFML/System/Clock.hpp>
#include <ctime>
#include <cmath>
#include <memory>

class MoveSearching {
public:
    MoveSearching(int depth, std::shared_ptr<bool> stopflag);
    ~MoveSearching();

    void setFlag(bool flag);
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
    Move bestMove;
    int analysisPoint;
    int analysisUncompletePoint;
    int score;

    int multiplyScore;
    int cntMoves;
    int id_search;
    bool isSearch;
    bool isSearchComplete;

    std::shared_ptr<bool> stopflag;
};

#endif