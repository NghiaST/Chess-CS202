#include "BitboardProcess.hpp"

void BitboardProcess::buildMoves(std::vector<Move> &moves, int startSquare, ulong bit, Move::FLAG flag) {
    while (bit) {
        int targetSquare = Bits::PopBit(bit);
        moves.push_back(Move(startSquare, targetSquare, flag));
    }
}

std::vector<Move> BitboardProcess::getPseudoMoves(int startSquare, int piece) {
    if (piece == PIECE::None) return std::vector<Move>();
    bool isWhiteTurn = PIECE::isWhite(piece);
    int pieceType = PIECE::PieceType(piece);
    switch (pieceType) {
        case 1:
            return getPawnMoves(startSquare, isWhiteTurn);
        case 2:
            return getKnightMoves(startSquare);
        case 3:
            return getBishopMoves(startSquare);
        case 4:
            return getRookMoves(startSquare);
        case 5:
            return getQueenMoves(startSquare);
        case 6:
            return getKingMoves(startSquare, isWhiteTurn);
        default:
            return std::vector<Move>();
    }
}

std::vector<Move> BitboardProcess::getPawnMoves(int startSquare, bool isWhiteTurn) {
    std::vector<Move> moves;
    ulong bitATK, bitEnpassant;
    int rank = startSquare / 8;
    int playerRank = isWhiteTurn ? rank : 7 - rank;

    if (isWhiteTurn) {
        if (rank < 6) moves.push_back(Move(startSquare, startSquare + 8, Move::FLAG::NoFlag));
        if (rank == 1) moves.push_back(Move(startSquare, startSquare + 16, Move::FLAG::PawnTwoStep));
        if (rank == 6) {
            moves.push_back(Move(startSquare, startSquare + 8, Move::FLAG::PromotionQueen));
            moves.push_back(Move(startSquare, startSquare + 8, Move::FLAG::PromotionRook));
            moves.push_back(Move(startSquare, startSquare + 8, Move::FLAG::PromotionBishop));
            moves.push_back(Move(startSquare, startSquare + 8, Move::FLAG::PromotionKnight));
        }
        bitATK = BitboardUtility::WhitePawnAttacks[startSquare];
        bitEnpassant = BitboardUtility::WhitePawnEnpassant[startSquare];
    } 
    else {
        if (rank > 1) moves.push_back(Move(startSquare, startSquare - 8, Move::FLAG::NoFlag));
        if (rank == 6) moves.push_back(Move(startSquare, startSquare - 16, Move::FLAG::PawnTwoStep));
        if (rank == 1) {
            moves.push_back(Move(startSquare, startSquare - 8, Move::FLAG::PromotionQueen));
            moves.push_back(Move(startSquare, startSquare - 8, Move::FLAG::PromotionRook));
            moves.push_back(Move(startSquare, startSquare - 8, Move::FLAG::PromotionBishop));
            moves.push_back(Move(startSquare, startSquare - 8, Move::FLAG::PromotionKnight));
        }
        bitATK = BitboardUtility::BlackPawnAttacks[startSquare];
        bitEnpassant = BitboardUtility::BlackPawnEnpassant[startSquare];
    }
    if (playerRank == 6) {
        buildMoves(moves, startSquare, bitATK, Move::FLAG::PromotionQueen);
        buildMoves(moves, startSquare, bitATK, Move::FLAG::PromotionRook);
        buildMoves(moves, startSquare, bitATK, Move::FLAG::PromotionBishop);
        buildMoves(moves, startSquare, bitATK, Move::FLAG::PromotionKnight);
    }
    else {
        buildMoves(moves, startSquare, bitATK, Move::FLAG::NoFlag);
    }
    buildMoves(moves, startSquare, bitEnpassant, Move::FLAG::EnPassant);
    return moves;
}

std::vector<Move> BitboardProcess::getKnightMoves(int startSquare) {
    std::vector<Move> moves;
    ulong bit = BitboardUtility::KnightMoves[startSquare];
    buildMoves(moves, startSquare, bit, Move::FLAG::NoFlag);
    return moves;
}

std::vector<Move> BitboardProcess::getBishopMoves(int startSquare) {
    std::vector<Move> moves;
    ulong bit = BitboardUtility::BishopMoves[startSquare];
    buildMoves(moves, startSquare, bit, Move::FLAG::NoFlag);
    return moves;
}

std::vector<Move> BitboardProcess::getRookMoves(int startSquare) {
    std::vector<Move> moves;
    ulong bit = BitboardUtility::RookMoves[startSquare];
    buildMoves(moves, startSquare, bit, Move::FLAG::NoFlag);
    return moves;
}

std::vector<Move> BitboardProcess::getQueenMoves(int startSquare) {
    std::vector<Move> moves;
    ulong bit = BitboardUtility::QueenMoves[startSquare];
    buildMoves(moves, startSquare, bit, Move::FLAG::NoFlag);
    return moves;
}

std::vector<Move> BitboardProcess::getKingMoves(int startSquare, bool isWhiteTurn) {
    std::vector<Move> moves;
    ulong bit = BitboardUtility::KingMoves[startSquare];
    ulong bitCastles;
    if (isWhiteTurn) {
        bitCastles = BitboardUtility::WhiteKingCastles[startSquare];
    } else {
        bitCastles = BitboardUtility::BlackKingCastles[startSquare];
    }
    buildMoves(moves, startSquare, bit, Move::FLAG::NoFlag);
    buildMoves(moves, startSquare, bitCastles, Move::FLAG::Castle);
    return moves;
}

ulong BitboardProcess::getAttackedSquares(int startSquare, int piece) {
    if (piece == PIECE::None) return 0ULL;
    bool isWhiteTurn = PIECE::isWhite(piece);
    int pieceType = PIECE::PieceType(piece);
    BitboardUtility::Initialize();
    switch (pieceType) {
        case PIECE::Pawn:
            if (isWhiteTurn) {
                return BitboardUtility::WhitePawnAttacks[startSquare];
            }
            else {
                return BitboardUtility::BlackPawnAttacks[startSquare];
            }
        case PIECE::Knight:
            return BitboardUtility::KnightMoves[startSquare];
        case PIECE::Bishop:
            return BitboardUtility::BishopMoves[startSquare];
        case PIECE::Rook:
            return BitboardUtility::RookMoves[startSquare];
        case PIECE::Queen:
            return BitboardUtility::QueenMoves[startSquare];
        case PIECE::King:
            return BitboardUtility::KingMoves[startSquare];
        default:
            return 0ULL;
    }
}
