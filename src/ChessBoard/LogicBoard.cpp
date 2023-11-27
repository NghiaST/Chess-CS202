#include <ChessBoard/LogicBoard.hpp>

LogicBoard::LogicBoard() 
  : Board()
{
    Reset();
    LoadBasicPosition();
    this->mIsMovesGeneratorInCache = false;
}

LogicBoard::~LogicBoard() {}

/// Accessors

int LogicBoard::getKingSquareIndex(bool colorTurn) const {
    for(int i = 0; i < 64; i++) {
        if (pieces[i] == (PIECE::King + PIECE::boolToColor(colorTurn))) {
            return i;
        }
    }
    return -1;
}

// Loading Positions

void LogicBoard::LoadPosition(PositionInfo posInfo) {
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

void LogicBoard::LoadPosition(std::string FEN_notation) {
    PositionInfo posInfo = Fen::FenToPosition(FEN_notation);
    LoadPosition(posInfo);
}

void LogicBoard::LoadBasicPosition() {
    LoadPosition(Fen::StartPosition);
}

void LogicBoard::Reset() {
    gameStateHistory.clear();
    movesHistory.clear();
    presentGameState = GameState();
    gameStateHistory.push_back(presentGameState);
    mIsWhiteTurn = true;
    cntMoves = 0;
    mUndoMoves.clear();
    mIsMovesGeneratorInCache = false;
}

bool LogicBoard::isNextMoveImpossible() {
    GenerateMovesCache();
    return movesGeneratorCache.empty();
}

bool LogicBoard::isFiftyMove() {
    return presentGameState.fiftyMoveCounter > 100;
}

void LogicBoard::MovePiece(int piece, int startSquare, int targetSquare) {
    // iBoard.removePieceAtSquare(piece, startSquare);
    // iBoard.addPieceAtSquare(piece, targetSquare);
    pieces[startSquare] = PIECE::None;
    pieces[targetSquare] = piece;
}

void LogicBoard::GenerateMovesCache() {
    if (mIsMovesGeneratorInCache) return;
    movesGeneratorCache = GenerateMoves();
    mIsMovesGeneratorInCache = true;
}
