#ifndef __Board_hpp__
#define __Board_hpp__

#include <DataControl/Include.hpp>
#include <Helpers/Fen.hpp>
#include <ChessBoard/GameState.hpp>
#include <ChessBoard/BitboardProcess.hpp>
#include <ChessBoard/LogicBoardStandard.hpp>
#include <vector>

class Board : public LogicBoardStandard {
public:
    // Constructors and Destructor
    Board();
    Board(const Board &board);
    ~Board();
    
    // Loading Positions
    void LoadPosition(PositionInfo posInfo);
    void LoadPosition(std::string FEN_notation);
    void LoadBasicPosition();
    void Reset();

    // Game Functions
    void NewGame();
    void MoveCache(Move move);
    bool UndoMoveCache();
    bool RedoMoveCache();

    // Accessors
    bool isUndoPossible() const;
    bool isRedoPossible() const;

private:
    std::vector<Move> mUndoMoves;
};

#endif