#ifndef __Board_hpp__
#define __Board_hpp__

#include "../DataControl/Include.hpp"
#include "../Helpers/Fen.hpp"
#include "GameState.hpp"
#include "BitboardProcess.hpp"
#include <vector>

class Board {
public:
    // Constructors and Destructor
    Board();
    Board(const Board &board);
    ~Board();
    
    // Accessors
    bool ifWhiteTurn() const;
    std::vector<int> getAllPieces() const;
    std::vector<Move> getLegalMoveAt(int startSquare);
    std::vector<Move> getLegalMoveList();
    const GameState getGameState() const;
    int getPiece(int rank, int file) const;
    int getPiece(int square) const;
    int getKingSquareIndex(bool colorTurn) const;

    bool isHistoryEmpty() const;
    int getMoveCount() const;
    Move getLastMove() const;
    std::vector<Move> getMovesHistory() const;

    // Move Validation
    bool ifCheck() const;
    bool ifCheckMate();
    bool ifStaleMate();
    bool isBoardLegal();
    bool isPseudoMoveLegal(Move move);

    // Loading Positions
    void LoadPosition(PositionInfo posInfo);
    void LoadPosition(std::string FEN_notation);
    void LoadBasicPosition();
    void Reset();

    // Game Functions
    void NewGame();
    void MakeMove(Move move, bool inSearch = false);
    void UnmakeMove(Move move, bool inSearch = false);
    void UndoMove();
    void MovePiece(int piece, int startSquare, int targetSquare);

private:
    // Private Helper Functions
    bool isSquareUnderAttack(int targetSquare, bool isWhiteTurn) const;
    bool isPseudoMoveLegalWithoutCheck(Move move) const;
    std::vector<Move> getPseudoLegalMoveList();
    std::vector<Move> getPseudoLegalMoveAt(int startSquare);
    ulong getAttackedSquares(bool isYourTurn) const;
    bool isPreventPiece(int startSquare, int targetSquare) const;

protected:
    // Member Variables
    std::vector<int> pieces;
    bool isWhiteTurn;
    int cntMoves;
    std::vector<Move> possibleMoveList;
    std::vector<Move> movesHistory;
    std::vector<GameState> gameStateHistory;
    GameState presentGameState;
};
#endif