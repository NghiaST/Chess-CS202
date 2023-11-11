#ifndef __GameState_hpp__
#define __GameState_hpp__

#include <SFML/Graphics.hpp>

// namespace Chess::DataManager {

typedef unsigned long long ulong;

struct GameState {
public:
    GameState();
    GameState(int capturedPieceType, int enPassantFile, int castlingRights, int fiftyMoveCounter, ulong zobristKey = 0);

    bool IsKingsideCastle(bool white) const;
    bool IsQueensideCastle(bool white) const;
    bool IsCastlePossible(bool isWhiteTurn, bool isKingside) const;

public:
    static const int ClearWhiteCastleMask = 0b1100;
    static const int ClearBlackCastleMask = 0b0011;
    static const int ClearWhiteKingsideMask = 0b1110;
    static const int ClearWhiteQueensideMask = 0b1101;
    static const int ClearBlackKingsideMask = 0b1011;
    static const int ClearBlackQueensideMask = 0b0111;

public:
    int capturedPieceType;  /// (0 -> 22) if no piece was captured, otherwise the type of the captured piece
    int enPassantFile;      /// (-1 -> 7) if no en passant square, otherwise the file of the en passant square
    int castlingRights;     /// 4 bits (0 -> 15): bit 0 = white kingside, bit 1 = white queenside, bit 2 = black kingside, bit 3 = black queenside
    int fiftyMoveCounter;   /// (0 - 100) number of half moves since the last capture or pawn move
    ulong zobristKey;       /// hashing key, use for check if two state is the same
};

// } // namespace Chess

#endif