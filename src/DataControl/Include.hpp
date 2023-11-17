#ifndef __Include_hpp__
#define __Include_hpp__

#include "Point.hpp"
#include "RenderPS.hpp"
#include <SFML/Graphics.hpp>

typedef unsigned long long ulong;

class PIECE {
public:
    enum TYPE {
        None    = 0,
        Pawn    = 1,
        Knight  = 2,
        Bishop  = 3,
        Rook    = 4,
        Queen   = 5,
        King    = 6
    };
    
    enum COLOR {
        White = 8,
        Black = 16
    };

    enum Piece {
        WhitePawn   = White | Pawn,
        WhiteKnight = White | Knight,
        WhiteBishop = White | Bishop,
        WhiteRook   = White | Rook,
        WhiteQueen  = White | Queen,
        WhiteKing   = White | King,

        BlackPawn   = Black | Pawn,
        BlackKnight = Black | Knight,
        BlackBishop = Black | Bishop,
        BlackRook   = Black | Rook,
        BlackQueen  = Black | Queen,
        BlackKing   = Black | King,

        AllType     = 7,
        AllColor    = 24
    };

    static int MakePiece(int pieceType, int pieceColor);
    static bool isWhite(int piece);
    static bool isPieceYourTurn(int piece, bool isWhite);
    static int boolToColor(bool isWhite);
    
    static int PieceColor(int piece);
    static int PieceType(int piece);

    static char PieceToSymbol(int piece);
    static int SymbolToPiece(char symbol);

    static char PieceTypeToChar(int pieceType);
    static char SymbolToPieceType(char symbol);

    static int PieceValue(int piece);
};

namespace CASTLING {
    const int WhiteKingSide  = 1;
    const int WhiteQueenSide = 2;
    const int BlackKingSide  = 4;
    const int BlackQueenSide = 8;
    const int All = 15;
};

namespace CHESS {
    enum COLOR {
        None  = -1,
        Black = 0,
        White = 1,
        Both  = 3
    };
};

namespace MOUSE {
    enum STATUS{
        None = 0,
        Pointed,
        Selected,
        Hold,
        Unpressed
    };
};

namespace INTERFACE {
    const sf::Vector2f WindowSize = sf::Vector2f(1024, 672);
    const double BoardLength = 64;
};

#endif