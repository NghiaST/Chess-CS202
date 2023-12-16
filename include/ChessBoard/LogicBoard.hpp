#ifndef __LogicBoard_hpp__
#define __LogicBoard_hpp__

#include <ChessBoard/Board.hpp>

class LogicBoard : public Board {
public:
    LogicBoard();
    virtual ~LogicBoard();

    // Accessors
    int getKingSquareIndex(bool colorTurn) const;

    // Loading Positions
    virtual void LoadPosition(PositionInfo posInfo);
    void LoadPosition(std::string FEN_notation);
    void LoadBasicPosition();
    virtual void Reset();

    // Move Validation
    bool isBoardValidByCustom();
    bool isNextMoveImpossible();
    bool isFiftyMove();

protected:
    // Functions
    /// Move Piece from startSquare to targetSquare, with targetSquare is emptySquare
    void MovePiece(int piece, int startSquare, int targetSquare);
    void GenerateMovesCache();

protected:
    bool mIsMovesGeneratorInCache;
    std::vector<Move> movesGeneratorCache;
};

#endif