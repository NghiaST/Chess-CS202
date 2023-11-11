#ifndef __Include_hpp__
#define __Include_hpp__
#include <SFML/Graphics.hpp>

typedef unsigned long long ulong;
class PIECE;
class CASTLING;
class MOUSE;
class INTERFACE;
class Point;

class PIECE {
public:
    /// Piece Type
    enum TYPE {
        None = 0,
        Pawn = 1,
        Knight = 2,
        Bishop = 3,
        Rook = 4,
        Queen = 5,
        King = 6
    };
    
    enum COLOR {
        White = 8,
        Black = 16
    };

    enum Pieces {
        WhitePawn = White | Pawn,
        WhiteKnight = White | Knight,
        WhiteBishop = White | Bishop,
        WhiteRook = White | Rook,
        WhiteQueen = White | Queen,
        WhiteKing = White | King,

        BlackPawn = Black | Pawn,
        BlackKnight = Black | Knight,
        BlackBishop = Black | Bishop,
        BlackRook = Black | Rook,
        BlackQueen = Black | Queen,
        BlackKing = Black | King,

        AllType = 7,
        AllColor = 24
    };

    static int MakePiece(int pieceType, int pieceColor);
    static bool isWhite(int piece);
    static bool isPieceYourTurn(int piece, bool isWhite);
    static int boolToColor(bool isWhite);
    
    static int PieceColor(int piece);
    static int PieceType(int piece);

    static char PieceToSymbol(int piece);
    static int SymbolToPiece(char symbol);

    static int PieceValue(int piece);
};
class CASTLING {
public:
    static const int WhiteKingSide = 1;
    static const int WhiteQueenSide = 2;
    static const int BlackKingSide = 4;
    static const int BlackQueenSide = 8;
    static const int All = 15;
};
class CHESS {
public:
    enum COLOR {
        None = -1,
        White = 0,
        Black = 1,
        Both = 3
    };
};

class MOUSE {
public:
    enum STATUS{NONE = 0, POINTED = 1, SELECTED = 2, HOLD = 3, UNPRESSED = 4};
};
class INTERFACE {
public:
    static const sf::Vector2f WindowSize;
    static const double BoardLength;
};

class Point {
public:
    Point();
    Point(double x, double y);
    Point(const sf::Vector2f& vector);
    Point(const sf::Vector2i& vector);
    Point(const sf::Vector2u& vector);
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator*(double other) const;
    friend Point operator*(double other, const Point& p);
    Point operator/(double other) const;
    Point div(int other) const;
    bool operator==(const Point& other) const;
    sf::Vector2f to2f() const;
    sf::Vector2i to2i() const;
    sf::Vector2u to2u() const;

public:
    double x, y;
};

// class Coord {
//     int rank, file;
//     Coord() : rank(-1), file(-1) {}
//     Coord(int rank, int file) : rank(rank), file(file) {}
// };

#endif