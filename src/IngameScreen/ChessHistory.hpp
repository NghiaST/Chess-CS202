#ifndef __ChessHistory_hpp__
#define __ChessHistory_hpp__
#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"

class MovingStore {
public:
    int preIndex, curIndex;
    int preData, curData;
    int moveStatus; // 0: illegal, 1: legal, 2: enpassant, 3: castle
    MovingStore();
    MovingStore(int preIndex, int curIndex, int preData, int curData, int moveStatus);
};

class ChessHistory {
protected:
    std::vector<MovingStore> moveList;
    int cntMove;

    // data for castling
    int dataMovingKing[2]; // white - black
    int dataMovingRook[2][2]; // white - black (left - right)
private:
    std::string encodeHistory();
    std::vector<MovingStore> decodeHistory(std::string encoded);
public:
    ChessHistory();
    ~ChessHistory();

    // Mutators
    void addMove(const MovingStore move);
    void popMove();
    void loadHistory(std::string filename = "dat/history.txt");
    void saveHistory(std::string filename = "dat/history.txt");
    void clear();
    
    // Accessors
    int getCntMove() const;
    MovingStore getLastMove() const;
    bool isCastlePossible(int color, int side) const;

    // Functions
    std::string getStringLastMove() const;
    std::string getStringHistory() const;
};

#endif