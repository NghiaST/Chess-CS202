#include <ChessBoard/Board.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <functional>
#include <bits.h>

// Constructor and Destructor

Board::Board()
: LogicBoardStandard()
{
    mIsWhiteTurn = true;
    cntMoves = 0;
    Reset();
    LoadBasicPosition();
}

Board::Board(const Board &board) {
    pieces = board.pieces;
    mIsWhiteTurn = board.mIsWhiteTurn;
    cntMoves = board.cntMoves;
    presentGameState = board.presentGameState;
    gameStateHistory = board.gameStateHistory;
    movesHistory = board.movesHistory;
}

Board::~Board() {}

// Loading Positions

void Board::LoadPosition(PositionInfo posInfo) {
    Reset();
    pieces = posInfo.squarePieces;
    mIsWhiteTurn = posInfo.whiteToMove;
    presentGameState.castlingRights = posInfo.castlingRights;
    presentGameState.enPassantFile = posInfo.enPassantFile;
    presentGameState.fiftyMoveCounter = posInfo.fiftyMoveCounter;
    cntMoves = posInfo.fullmoveNumber * 2 - (mIsWhiteTurn ? 2 : 1);

    presentGameState = GameState(PIECE::None, posInfo.enPassantFile, posInfo.castlingRights, posInfo.fiftyMoveCounter);
    gameStateHistory.push_back(presentGameState);
}

void Board::LoadPosition(std::string FEN_notation) {
    PositionInfo posInfo = Fen::FenToPosition(FEN_notation);
    LoadPosition(posInfo);
}

void Board::LoadBasicPosition() {
    LoadPosition(Fen::StartPosition);
}

void Board::Reset() {
    gameStateHistory.clear();
    movesHistory.clear();
    presentGameState = GameState();
    gameStateHistory.push_back(presentGameState);
    mIsWhiteTurn = true;
    cntMoves = 0;
    mUndoMoves.clear();
}

// Game Functions

void Board::NewGame() {
    LoadBasicPosition();
}

void Board::MoveCache(Move move) {
    mUndoMoves.clear();
    MakeMove(move, false);
}

bool Board::UndoMoveCache() {
    if (!isUndoPossible()) return false;
    printf("UNDO\n");
    Move lastMove = getLastMove();
    mUndoMoves.push_back(lastMove);
    UnmakeMove(lastMove, false);
    return true;
}

bool Board::RedoMoveCache() {
    if (!isRedoPossible()) return false;
    printf("REDO\n");
    Move lastMove = mUndoMoves.back();
    mUndoMoves.pop_back();
    MakeMove(lastMove);
    return true;
}

bool Board::isUndoPossible() const {
    return !isHistoryEmpty();
}

bool Board::isRedoPossible() const {
    return !mUndoMoves.empty();
}