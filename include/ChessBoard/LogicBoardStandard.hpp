#ifndef __MoveGenerator_hpp__
#define __MoveGenerator_hpp__

#include <vector>
#include <ChessBoard/GameState.hpp>

typedef unsigned long long ulong;
class Move;

class LogicBoard {
public:
    LogicBoard();
    virtual ~LogicBoard();

    // Accessors
    int getPiece(int rank, int file) const;
    int getPiece(int square) const;
    virtual int getKingSquareIndex(bool colorTurn) const;
    std::vector<int> getAllPieces() const;
    const GameState getGameState() const;
    bool isWhiteTurn() const;

    // Accessors - Move History
    bool isHistoryEmpty() const;
    int getMoveCount() const;
    Move getLastMove() const;
    std::vector<Move> getMovesHistory() const;

    // Move Validation
    virtual bool isCheck() const = 0;
    virtual bool isCheckMate() = 0;
    virtual bool isStaleMate() = 0;
    virtual bool isBoardLegal() = 0;

    virtual void MakeMove(Move move, bool inSearch = false) = 0;
    virtual void UnmakeMove(Move move, bool inSearch = false) = 0;

    // Functions
    virtual std::vector<Move> GenerateMoves() = 0;
    virtual std::vector<Move> GenerateMovesSquare(int startSquare) = 0;
    /// Move has not been validated correctly for that piece
    virtual bool isMoveLegal(Move move) = 0;
    // Move getFlagMove(int startSquare, int targetSquare) = 0; { return updateFlag(Move(startSquare, targetSquare, Move::FLAG::None)).flag; }
    // virtual Move updateFlag(Move move) = 0;

protected:
    // Functions
    /// Move Piece from startSquare to targetSquare, with targetSquare is emptySquare
    void MovePiece(int piece, int startSquare, int targetSquare);

protected:
    std::vector<int> pieces;
    bool mIsWhiteTurn;
    int cntMoves;
    std::vector<Move> movesHistory;
    std::vector<GameState> gameStateHistory;
    GameState presentGameState;

    bool mIsMovesInCache;
    std::vector<Move> mGenerateMovesInCache;
};

class LogicBoardStandard : public LogicBoard {
public:
    LogicBoardStandard();
    virtual ~LogicBoardStandard();

    // Move Validation
    bool isCheck() const;
    bool isCheckMate();
    bool isStaleMate();
    bool isBoardLegal();

    void MakeMove(Move move, bool inSearch = false);
    void UnmakeMove(Move move, bool inSearch = false);

    // Functions
    std::vector<Move> GenerateMoves();
    std::vector<Move> GenerateMovesSquare(int startSquare);
    /// Move has not been validated correctly for that piece
    bool isMoveLegal(Move move);
    // virtual Move getFlagMove(int startSquare, int targetSquare) = 0;

private:
    /// Check if this move is pseudo move
    bool isMovePseudo(Move move) const;

    /// Move is legal in terms of piece movement, but not in terms of board state
    bool isPseudoMoveLegal(Move move);

    /// assert that startPiece has the same color as mIsWhiteTurn
    bool isPseudoMoveLegalNotKingCheck(Move move) const;

    std::vector<Move> GeneratePseudoMovesNotKingCheck() const;
    std::vector<Move> GeneratePseudoMovesSquareNotKingCheck(int startSquare);
    ulong getAttackedSquares(bool isYourTurn) const;
    bool isSquareUnderAttack(int targetSquare, bool mIsWhiteTurn) const;
    bool isPreventPiece(int startSquare, int targetSquare) const;
};

#endif