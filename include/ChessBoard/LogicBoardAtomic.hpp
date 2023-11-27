#ifndef __LogicBoardAtomic_hpp__
#define __LogicBoardAtomic_hpp__

#include <ChessBoard/LogicBoard.hpp>
#include <vector>

typedef unsigned long long ulong;
class Move;

class LogicBoardAtomic : public LogicBoard {
public:
    LogicBoardAtomic();
    virtual ~LogicBoardAtomic();
    Board* clone() const;

    void LoadPosition(PositionInfo posInfo) override;
    void Reset() override;

    // Move Validation
    bool isCheck() const;
    bool isCheckMate();
    bool isStaleMate();
    bool isBoardLegal();
    bool isEndGame();
    Board::EndFlag getEndFlag();
    bool isWin();
    bool isDraw();

    void MakeMove(Move move, bool inSearch = false);
    void UnmakeMove(Move move, bool inSearch = false);

    // Functions
    std::vector<Move> GenerateMoves();
    std::vector<Move> GenerateMovesSquare(int startSquare);
    /// Move has not been validated correctly for that piece
    bool isMoveLegal(Move move);
    // virtual Move getFlagMove(int startSquare, int targetSquare) = 0;

private:
    bool isKingDead() const;

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

private:
    std::vector<std::vector<int>> piecesHistory;
};

#endif