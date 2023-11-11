#include "Include.hpp"

const sf::Vector2f INTERFACE::WindowSize = sf::Vector2f(1024, 672);
const double INTERFACE::BoardLength = 64;

int PIECE::MakePiece(int pieceType, int pieceColor) {
    return pieceType | pieceColor;
}
bool PIECE::isWhite(int piece) {
    return (piece & White) != 0;
}
bool PIECE::isPieceYourTurn(int piece, bool isWhiteTurn) {
    if (piece == None) return false;
    return (isWhite(piece) == isWhiteTurn);
}
int PIECE::boolToColor(bool isWhite) {
    return isWhite ? White : Black;
}
int PIECE::PieceColor(int piece)
{
    return piece & AllColor;
}
int PIECE::PieceType(int piece) {
    return piece & AllType;
}
char PIECE::PieceToSymbol(int piece) {
    switch (piece) {
        case WhitePawn: return 'P';
        case WhiteKnight: return 'N';
        case WhiteBishop: return 'B';
        case WhiteRook: return 'R';
        case WhiteQueen: return 'Q';
        case WhiteKing: return 'K';
        case BlackPawn: return 'p';
        case BlackKnight: return 'n';
        case BlackBishop: return 'b';
        case BlackRook: return 'r';
        case BlackQueen: return 'q';
        case BlackKing: return 'k';
        default: return ' ';
    }
}
int PIECE::SymbolToPiece(char symbol) {
    switch (symbol) {
        case 'P': return WhitePawn;
        case 'N': return WhiteKnight;
        case 'B': return WhiteBishop;
        case 'R': return WhiteRook;
        case 'Q': return WhiteQueen;
        case 'K': return WhiteKing;
        case 'p': return BlackPawn;
        case 'n': return BlackKnight;
        case 'b': return BlackBishop;
        case 'r': return BlackRook;
        case 'q': return BlackQueen;
        case 'k': return BlackKing;
        default: return 0;
    }
}

int PIECE::PieceValue(int piece) {
    switch (piece) {
        case WhitePawn: return 100;
        case WhiteKnight: return 320;
        case WhiteBishop: return 330;
        case WhiteRook: return 500;
        case WhiteQueen: return 900;
        case WhiteKing: return 0;
        case BlackPawn: return -100;
        case BlackKnight: return -320;
        case BlackBishop: return -330;
        case BlackRook: return -500;
        case BlackQueen: return -900;
        case BlackKing: return 0;
        default: return 0;
    }
}

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(const sf::Vector2f& vector) : x(vector.x), y(vector.y) {}
Point::Point(const sf::Vector2i& vector) : x(vector.x), y(vector.y) {}
Point::Point(const sf::Vector2u& vector) : x(vector.x), y(vector.y) {}
Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}
Point Point::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}
Point Point::operator*(double other) const {
    return Point(x * other, y * other);
}
Point operator*(double other, const Point& p) {
    return Point(p.x * other, p.y * other);
}
Point Point::operator/(double other) const {
    return Point(x / other, y / other);
}
Point Point::div(int other) const
{
    return Point((int)x / other, (int)y / other);
}
bool Point::operator==(const Point &other) const {
    return (x == other.x && y == other.y);
}
sf::Vector2f Point::to2f() const
{
    return sf::Vector2f(x, y);
}
sf::Vector2i Point::to2i() const {
    return sf::Vector2i((int)x, (int)y);
}
sf::Vector2u Point::to2u() const {
    return sf::Vector2u((unsigned int)x, (unsigned int)y);
}
