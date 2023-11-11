#include "Bitboard.hpp"
#include <cmath>

std::vector<ulong> BitboardUtility::KnightMoves = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::BishopMoves = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::RookMoves = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::QueenMoves = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::KingMoves = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::WhitePawnAttacks = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::BlackPawnAttacks = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::WhiteKingCastles = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::BlackKingCastles = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::WhitePawnEnpassant = std::vector<ulong>(64);
std::vector<ulong> BitboardUtility::BlackPawnEnpassant = std::vector<ulong>(64);

int Bits::PopBit(ulong& iBit) {
    if (iBit == 0) return -1;
    ulong ret = iBit & (~iBit + 1);
    iBit ^= ret;
    return (int)log2(ret);// __builtin_ctzll(ret);
}

void Bits::OnBit(ulong& iBit, int index) {
    iBit |= 1ULL << index;
}

void Bits::OffBit(ulong& iBit, int index) {
    iBit &= ~(1ULL << index);
}

void Bits::ToggleBit(ulong& iBit, int index) {
    iBit ^= 1ULL << index;
}

bool Bits::GetBit(ulong& iBit, int index) {
    return (iBit >> index) & 1ULL;
}

void BitboardUtility::Initialize() {
    KnightMoves = std::vector<ulong>(64);
    BishopMoves = std::vector<ulong>(64);
    RookMoves = std::vector<ulong>(64);
    QueenMoves = std::vector<ulong>(64);
    KingMoves = std::vector<ulong>(64);
    WhitePawnAttacks = std::vector<ulong>(64);
    BlackPawnAttacks = std::vector<ulong>(64);
    WhiteKingCastles = std::vector<ulong>(64);
    BlackKingCastles = std::vector<ulong>(64);
    WhitePawnEnpassant = std::vector<ulong>(64);
    BlackPawnEnpassant = std::vector<ulong>(64);

    std::array<std::pair<int, int>, 8> kingGo = {
        std::make_pair(1, 0),
        std::make_pair(0, 1),
        std::make_pair(-1, 0),
        std::make_pair(0, -1),
        std::make_pair(1, 1),
        std::make_pair(-1, 1),
        std::make_pair(-1, -1),
        std::make_pair(1, -1)
    };
    std::array<std::pair<int, int>, 8> knightGo = {
        std::make_pair(1, 2),
        std::make_pair(2, 1),
        std::make_pair(2, -1),
        std::make_pair(1, -2),
        std::make_pair(-1, -2),
        std::make_pair(-2, -1),
        std::make_pair(-2, 1),
        std::make_pair(-1, 2)
    };
    std::array<std::pair<int, int>, 2> whitepawnATK = {
        std::make_pair(1, -1),
        std::make_pair(1, 1)
    };
    std::array<std::pair<int, int>, 2> blackpawnATK = {
        std::make_pair(-1, -1),
        std::make_pair(-1, 1)
    };
    std::array<std::pair<int, int>, 4> bishopStep = {
        std::make_pair(1, 1),
        std::make_pair(-1, 1),
        std::make_pair(-1, -1),
        std::make_pair(1, -1)
    };
    std::array<std::pair<int, int>, 4> rookStep = {
        std::make_pair(1, 0),
        std::make_pair(0, 1),
        std::make_pair(-1, 0),
        std::make_pair(0, -1)
    };
    std::array<std::pair<int, int>, 8> queenStep = {
        std::make_pair(1, 0),
        std::make_pair(0, 1),
        std::make_pair(-1, 0),
        std::make_pair(0, -1),
        std::make_pair(1, 1),
        std::make_pair(-1, 1),
        std::make_pair(-1, -1),
        std::make_pair(1, -1)
    };

    auto ValidSquare = [](int rank, int file) -> bool {
        return 0 <= rank && rank < 8 && 0 <= file && file < 8;
    };

    auto ProcessSquare = [&](int rank, int file) -> void {
        int index = rank * 8 + file;

        // King Castles
        {
            if (rank == 0 && file == 4) {
                WhiteKingCastles[index] |= 1ULL << 2;
                WhiteKingCastles[index] |= 1ULL << 6;
            }
            if (rank == 7 && file == 4) {
                BlackKingCastles[index] |= 1ULL << 58;
                BlackKingCastles[index] |= 1ULL << 62;
            }
        }

        for(int dir = 0; dir < 8; dir++) {
            // king moves
            {
                int newRank = rank + kingGo[dir].first;
                int newFile = file + kingGo[dir].second;
                if(ValidSquare(newRank, newFile)) {
                    int newIndex = newRank * 8 + newFile;
                    KingMoves[index] |= 1ULL << newIndex;
                }
            }

            // knight attacks (moves)
            {
                int newRank = rank + knightGo[dir].first;
                int newFile = file + knightGo[dir].second;
                if(ValidSquare(newRank, newFile)) {
                    int newIndex = newRank * 8 + newFile;
                    KnightMoves[index] |= 1ULL << newIndex;
                }
            }

            // pawn attacks
            if (dir < 2) {
                {
                    int newRank = rank + whitepawnATK[dir].first;
                    int newFile = file + whitepawnATK[dir].second;
                    if(ValidSquare(newRank, newFile)) {
                        int newIndex = newRank * 8 + newFile;
                        WhitePawnAttacks[index] |= 1ULL << newIndex;
                    }
                }
                {
                    int newRank = rank + blackpawnATK[dir].first;
                    int newFile = file + blackpawnATK[dir].second;
                    if(ValidSquare(newRank, newFile)) {
                        int newIndex = newRank * 8 + newFile;
                        BlackPawnAttacks[index] |= 1ULL << newIndex;
                    }
                }
            }

            // pawn Enpassant
            {
                if (rank == 4) 
                    WhitePawnEnpassant[index] = WhitePawnAttacks[index];
                if (rank == 3)
                    BlackPawnEnpassant[index] = BlackPawnAttacks[index];
            }

            // bishop moves
            if (dir < 4) {
                int newRank = rank + bishopStep[dir].first;
                int newFile = file + bishopStep[dir].second;
                while(ValidSquare(newRank, newFile)) {
                    int newIndex = newRank * 8 + newFile;
                    BishopMoves[index] |= 1ULL << newIndex;
                    newRank += bishopStep[dir].first;
                    newFile += bishopStep[dir].second;
                }
            }

            // rook moves
            if (dir < 4) {
                int newRank = rank + rookStep[dir].first;
                int newFile = file + rookStep[dir].second;
                while(ValidSquare(newRank, newFile)) {
                    int newIndex = newRank * 8 + newFile;
                    RookMoves[index] |= 1ULL << newIndex;
                    newRank += rookStep[dir].first;
                    newFile += rookStep[dir].second;
                }
            }

            // queen moves
            {
                int newRank = rank + queenStep[dir].first;
                int newFile = file + queenStep[dir].second;
                while(ValidSquare(newRank, newFile)) {
                    int newIndex = newRank * 8 + newFile;
                    QueenMoves[index] |= 1ULL << newIndex;
                    newRank += queenStep[dir].first;
                    newFile += queenStep[dir].second;
                }
            }
        }
    };
    for (int i = 0; i < 64; i++) {
        int rank = i / 8;
        int file = i % 8;
        ProcessSquare(rank, file);
    }
}

ulong BitboardUtility::PawnAttack(ulong iBit, bool isWhite) {
    if (isWhite) {
        return ((iBit << 7) & notAFile) | ((iBit << 9) & notHFile);
    }
    else {
        return ((iBit >> 7) & notAFile) | ((iBit >> 9) & notHFile);
    }
}

ulong BitboardUtility::Shift(ulong iBit, int shift) {
    if (shift > 0) {
        return iBit << shift;
    }
    else {
        return iBit >> (-shift);
    }
}