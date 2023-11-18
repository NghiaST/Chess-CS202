#ifndef __BitboardProcess_hpp__
#define __BitboardProcess_hpp__

#include <ChessBoard/Bitboard.hpp>
#include <ChessBoard/Move.hpp>

class BitboardProcess {
private:
    static void buildMoves(std::vector<Move>& moves, int startSquare, ulong bit, Move::FLAG flag);
public:
    static std::vector<Move> getPseudoMoves(int startSquare, int piece);
    static std::vector<Move> getPawnMoves(int startSquare, bool isWhiteTurn);
    static std::vector<Move> getKnightMoves(int startSquare);
    static std::vector<Move> getBishopMoves(int startSquare);
    static std::vector<Move> getRookMoves(int startSquare);
    static std::vector<Move> getQueenMoves(int startSquare);
    static std::vector<Move> getKingMoves(int startSquare, bool isWhiteTurn);

    static ulong getAttackedSquares(int startSquare, int piece);
// public:
    // static std::vector<Move> getAllPseudoLegalMoves(std::vector<int> pieces);
};

#endif