#ifndef __MoveUtility_hpp__
#define __MoveUtility_hpp__

#include <string>
class Move;
class Board;

class MoveUtility {
public:
    /// UCI Name: /// Converts a moveName into internal move representation
    /// Name is expected in format: "e2e4"
    /// Promotions can be written with or without equals sign, for example: "e7e8=q" or "e7e8q"
    static Move GetMoveFromNameUCI(std::string moveName, Board board);
    static std::string GetMoveNameUCI(Move move);

    /// Get name of move in Standard Algebraic Notation (SAN)
    /// Examples: "e4", "Bxf7+", "O-O", "Rh8#", "Nfd2"
    /// Note, the move must not yet have been made on the board
    static std::string GetMoveNameSAN(Move move, Board board);
    static Move GetMoveFromSAN(std::string algebraicNotation, Board board);
};

#endif