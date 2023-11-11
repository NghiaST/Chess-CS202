#ifndef __Fen_hpp__
#define __Fen_hpp__

#include "../DataControl/Include.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

struct PositionInfo {
public:
    PositionInfo(std::string fen);
    PositionInfo(std::vector<int> squarePieces, bool whiteToMove, int castlingRights, int enPassantFile, int fiftyMoveCounter, int fullmoveNumber);
public:
    std::vector<int> squarePieces;
    bool whiteToMove;
    int castlingRights;
    int enPassantFile;
    int fiftyMoveCounter;
    int fullmoveNumber;
};

// Helper class for dealing with FEN strings
class Fen {
public:
    static const std::string StartPosition;
    static std::string PositionToFen(PositionInfo position);
    static PositionInfo FenToPosition(std::string fen);
    // static std::string CurrentFen(const AIBoard* board, bool alwaysIncludeEPSquare = true);
    // static bool EnPassantCanBeCaptured(int epFileIndex, int epRankIndex, Board board);
    // static std::string FlipFen(std::string fen);
};

#endif