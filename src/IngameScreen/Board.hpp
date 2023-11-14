#ifndef __Board_hpp__
#define __Board_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/StaticButton.hpp"
#include "../DataControl/Button.hpp"
#include "Piece.hpp"
#include "BoardPrint.hpp"
#include <vector>
#include "GameState.hpp"
#include "Fen.hpp"
#include "BitboardProcess.hpp"

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
    int getPiece(int rank, int file) const;
    int getPiece(int square) const;
    int getKingSquareIndex(bool colorTurn) const;

    bool isHistoryEmpty() const;
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
    void UnmakeMove(Move move, bool inSearch = true);
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
    int cntMove;
    std::vector<Move> possibleMoveList;
    std::vector<Move> movesHistory;
    std::vector<GameState> gameStateHistory;
    GameState presentGameState;
};
#endif