#include <ChessBoard/Board.hpp>
#include <ChessBoard/LogicBoard.hpp>
#include <ChessBoard/LogicBoardStandard.hpp>
#include <ChessBoard/LogicBoardKingHill.hpp>
#include <ChessBoard/LogicBoardAtomic.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <functional>
#include <bits.h>

// Constructor and Destructor

Board::Board() {
    this->mIsWhiteTurn = true;
    this->cntMoves = 0;
    this->presentGameState = GameState();
    this->gameStateHistory.push_back(presentGameState);

    mIsWhiteTurn = true;
    cntMoves = 0;
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

// Accessors

void Board::setPiece(int square, int piece) {
    pieces[square] = piece;
}

int Board::getPiece(int rank, int file) const
{
    return pieces[rank * 8 + file];
}

int Board::getPiece(int square) const {
    return pieces[square];
}

std::vector<int> Board::getAllPieces() const {
    return this->pieces;
}

bool Board::isWhiteTurn() const {
    return mIsWhiteTurn;
}

const GameState Board::getGameState() const {
    return presentGameState;
}

// Accessors - Move History

bool Board::isHistoryEmpty() const {
    return movesHistory.size() == 0;
}

int Board::getMoveCount() const {
    return cntMoves;
}

Move Board::getLastMove() const
{
    return movesHistory.back();
}

std::vector<Move> Board::getMovesHistory() const {
    return movesHistory;
}

// Checking

bool Board::isUndoPossible() const {
    return !isHistoryEmpty();
}

bool Board::isRedoPossible() const {
    return !mUndoMoves.empty();
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

///--------------------------------------------

int Board::getKingSquareIndex(bool colorTurn) const {
    for(int i = 0; i < 64; i++) {
        if (pieces[i] == (PIECE::King + PIECE::boolToColor(colorTurn))) {
            return i;
        }
    }
    return -1;
}

Board *FactoryBoard::CreateBoard(std::string boardType) {
    if (boardType == "standard") {
        return new LogicBoardStandard();
    }
    else if (boardType == "kingofthehill") {
        return new LogicBoardKingHill();
    }
    else if (boardType == "atomic") {
        return new LogicBoardAtomic();
    }
    else {
        return new LogicBoardStandard();  
    }
}

SBoard::SBoard(std::string boardType) {
    this->board = FactoryBoard::CreateBoard(boardType);
}

SBoard::SBoard(const SBoard &sBoard) {
    this->board = sBoard.board->clone();
}

SBoard::~SBoard() {
    delete board;
}

SBoard &SBoard::operator=(const SBoard &sBoard) {
    delete board;
    this->board = sBoard.board->clone();
    return *this;
}

Board *SBoard::getBoard() const {
    return board;
}