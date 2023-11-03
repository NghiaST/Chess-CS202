#ifndef __Include_hpp__
#define __Include_hpp__
#include <SFML/Graphics.hpp>

class PIECE;
class CHESS;
class MOUSE;
class INTERFACE;
struct Point;

class PIECE {
public:
    enum TYPE{NONE = 0, KING = 1, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};
    static const int ALLTYPE = 7;
};
class CHESS {
public:
    enum COLOR{NONE = 0, WHITE = 8, BLACK = 16};
    static const int BLACKWHITE = COLOR::WHITE | COLOR::BLACK;
    static const int BOTHCOLOR = 24;
};
class MOUSE {
public:
    enum STATUS{NONE = 0, POINTED = 1, SELECTED = 2, HOLD = 3, UNPRESSED = 4};
};
class INTERFACE {
public:
    static const sf::Vector2f WINDOWSIZE;
    static const double SIZEBOARD;
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

#endif