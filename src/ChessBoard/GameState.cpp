#include <ChessBoard/GameState.hpp>

// namespace Chess::DataManager {
GameState::GameState()
{
    capturedPieceType = 0;
    enPassantFile = 0;
    castlingRights = 0b1111;
    fiftyMoveCounter = 0;
    zobristKey = 0;
}

GameState::GameState(int capturedPieceType, int enPassantFile, int castlingRights, int fiftyMoveCounter, ulong zobristKey)
{
    this->capturedPieceType = capturedPieceType;
    this->enPassantFile = enPassantFile;
    this->castlingRights = castlingRights;
    this->fiftyMoveCounter = fiftyMoveCounter;
    this->zobristKey = zobristKey;
}

bool GameState::IsKingsideCastle(bool white) const
{
    int mask = white ? 1 : 4;
    return (castlingRights & mask) != 0;
}

bool GameState::IsQueensideCastle(bool white) const
{
    int mask = white ? 2 : 8;
    return (castlingRights & mask) != 0;
}

bool GameState::IsCastlePossible(bool isWhiteTurn, bool isKingside) const {
    return isKingside ? IsKingsideCastle(isWhiteTurn) : IsQueensideCastle(isWhiteTurn);
}

// }