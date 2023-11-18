#ifndef __Bitboard_hpp__
#define __Bitboard_hpp__

#include <vector>
#include <array>

typedef unsigned long long ulong;

class Bits {
public:
    static int PopBit(ulong& iBit);
    static void OnBit(ulong& iBit, int index);
    static void OffBit(ulong& iBit, int index);
    static void ToggleBit(ulong& iBit, int index);
    static bool GetBit(ulong& iBit, int index);
};

class BitboardUtility {
public:
    static void Initialize();
public:
    static const ulong FileA = 0x0101010101010101ULL;
    static const ulong notAFile = ~FileA;
    static const ulong notHFile = ~(FileA << 7);

    static const ulong Rank1 = 0xFF;
    static const ulong Rank2 = Rank1 << (8 * 1);
    static const ulong Rank3 = Rank1 << (8 * 2);
    static const ulong Rank4 = Rank1 << (8 * 3);
    static const ulong Rank5 = Rank1 << (8 * 4);
    static const ulong Rank6 = Rank1 << (8 * 5);
    static const ulong Rank7 = Rank1 << (8 * 6);
    static const ulong Rank8 = Rank1 << (8 * 7);

    static const ulong DiagonalA1H8 = 0x8040201008040201ULL;
    static const ulong DiagonalH1A8 = 0x0102040810204080ULL;

    static std::vector<ulong> KnightMoves;
    static std::vector<ulong> BishopMoves;
    static std::vector<ulong> RookMoves;
    static std::vector<ulong> QueenMoves;
    static std::vector<ulong> KingMoves;
    static std::vector<ulong> WhitePawnAttacks;
    static std::vector<ulong> BlackPawnAttacks;
    static std::vector<ulong> WhiteKingCastles;
    static std::vector<ulong> BlackKingCastles;
    static std::vector<ulong> WhitePawnEnpassant;
    static std::vector<ulong> BlackPawnEnpassant;
    // static std::vector<ulong> PawnPromotions;

    // static std::vector<ulong> KnightAttacks;
    // static std::vector<ulong> KingMoves;
    // static std::vector<ulong> WhitePawnAttacks;
    // static std::vector<ulong> BlackPawnAttacks;


    static ulong PawnAttack(ulong iBit, bool isWhite);
    static ulong Shift(ulong iBit, int shift);
};

#endif