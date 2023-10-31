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
    static const Point POSBOARD;
    static const double SIZEBOARD;
};
struct Point {
    double x, y;
    Point(double x = 0, double y = 0);
    Point(const sf::Vector2i& vector) : x(vector.x), y(vector.y) {}
    Point(const sf::Vector2u& vector) : x(vector.x), y(vector.y) {}
    Point(const sf::Vector2f& vector) : x(vector.x), y(vector.y) {}
    Point operator + (const Point& p) const { return Point(x + p.x, y + p.y); }
    Point operator - (const Point& p) const { return Point(x - p.x, y - p.y); }
    Point operator * (const double& k) const { return Point(x * k, y * k); }
    Point operator / (const double& k) const { return Point(x / k, y / k); }
};

#endif