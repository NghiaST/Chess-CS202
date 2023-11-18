#include <DataControl/Point.hpp>

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
