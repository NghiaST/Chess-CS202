#ifndef __Point_hpp__
#define __Point_hpp__

#include <SFML/System/Vector2.hpp>

struct Point {
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

    double x, y;
};

#endif