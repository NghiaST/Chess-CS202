#ifndef __Board_hpp__
#define __Board_hpp__

#include <DataControl/Include.hpp>
#include <Helpers/Fen.hpp>
#include <ChessBoard/Move.hpp>
#include <ChessBoard/GameState.hpp>
#include <ChessBoard/BitboardProcess.hpp>
#include <vector>


class Board {
public:
    enum EndFlag {
        Unknown = 0,
        Checkmate,
        Stalemate,
        ThreefoldRep,
        FiftyMove,
        KingHill
    };

public:
    Board();
    Board(const Board &board);
    virtual Board* clone() const = 0;
    // Constructors and Destructor
    virtual ~Board();

    // Accessors
    int getPiece(int rank, int file) const;
    int getPiece(int square) const;
    std::vector<int> getAllPieces() const;
    const GameState getGameState() const;
    bool isWhiteTurn() const;

    // Accessors - Move History
    bool isHistoryEmpty() const;
    int getMoveCount() const;
    Move getLastMove() const;
    std::vector<Move> getMovesHistory() const;

    // Checking
    bool isUndoPossible() const;
    bool isRedoPossible() const;
    virtual int getKingSquareIndex(bool colorTurn) const;
    
    // Game Functions
    void NewGame();
    void MoveCache(Move move);
    bool UndoMoveCache();
    bool RedoMoveCache();
    
    // Loading Positions
    virtual void LoadPosition(PositionInfo posInfo) = 0;
    virtual void LoadPosition(std::string FEN_notation) = 0;
    virtual void LoadBasicPosition() = 0;
    virtual void Reset() = 0;

public: //--- logic functions, so all are pure virtual
    // Move Validation
    virtual bool isNextMoveImpossible() = 0;
    virtual bool isCheck() const = 0;
    virtual bool isCheckMate() = 0;
    virtual bool isStaleMate() = 0;
    virtual bool isBoardLegal() = 0;
    virtual bool isEndGame() = 0;
    virtual EndFlag getEndFlag() = 0;
    virtual bool isWin() = 0;
    virtual bool isDraw() = 0;

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
    std::vector<int> pieces;
    bool mIsWhiteTurn;
    int cntMoves;
    std::vector<Move> movesHistory;
    std::vector<GameState> gameStateHistory;
    GameState presentGameState;
    std::vector<Move> mUndoMoves;
    std::string boardType;  /// standard, kingofthehill, etc.
};

class LogicBoard;
class LogicBoardStandard;
class FactoryBoard {
public:
    static Board* CreateBoard(std::string boardType);
};

class SBoard {
public:
    SBoard(std::string boardType);
    SBoard(const SBoard& sBoard);
    ~SBoard();
    SBoard& operator = (const SBoard& sBoard);
    Board* getBoard() const;
private:
    Board* board;
};

#endif