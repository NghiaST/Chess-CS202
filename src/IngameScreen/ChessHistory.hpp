#ifndef __ChessHistory_hpp__
#define __ChessHistory_hpp__
#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "Move.hpp"

class ChessHistory {
public:
    ChessHistory();
    ~ChessHistory();

    // Mutators
    void addMove(const Move move);
    void popMove();
    void loadHistory(std::string filename = "dat/history.txt");
    void saveHistory(std::string filename = "dat/history.txt");
    void clear();
    
    // Accessors
    int getCntMove() const;
    Move getLastMove() const;
    bool isCastlePossible(int color, int side) const;

    // Functions
    std::string getStringMove(int index) const;
    std::string getStringLastMove() const;
    std::string getStringHistory() const;

    std::string encodeHistory();
    std::vector<Move> decodeHistory(std::string encoded);

private:
    std::vector<Move> moveList;
    int unknownMove;
    int cntMove;

    // store first move of king and rook
    int castlingRights[4]; // white kingside - white queenside - black kingside - black queenside
};

#endif