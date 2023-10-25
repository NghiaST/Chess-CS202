#ifndef __include_hpp__
#define __include_hpp__

namespace PIECE {
    enum TYPE{NONE = 0, KING = 1, QUEEN, BISHOP, KNIGHT, ROOK, PAWN};
    int ALLTYPE = 7;
};
namespace CHESS {
    enum COLOR{NONE = 0, WHITE = 8, BLACK = 16};
    int BLACKWHITE = COLOR::WHITE | COLOR::BLACK;
    int ALLCOLOR = 24;
};
namespace MOUSE {
    enum STATUS{NONE = 0, POINTED = 1, SELECTED = 2, HOLD = 3, UNPRESSED = 4};
};

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

#endif