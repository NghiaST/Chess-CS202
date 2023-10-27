#include "Include.hpp"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

const Point INTERFACE::POSBOARD = Point(50, 40);
const double INTERFACE::SIZEBOARD = 70;