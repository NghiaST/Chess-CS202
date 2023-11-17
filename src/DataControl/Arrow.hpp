#ifndef __Arrow_hpp__
#define __Arrow_hpp__

#include "Color.hpp"
#include "Include.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class ArrowShape : public sf::Drawable {
public:
    ArrowShape();
    ArrowShape(Point startPoint, Point targetPoint, const ColorButMulti& ColorButMulti, int radiusTriangle, int lineWidth);
    ~ArrowShape();

    void setColorBM(ColorButMulti colorButMulti);
    void setRadiusTriangle(int radiusTriangle);
    void setLineWidth(int lineWidth);
    void setArrowPosition(Point startPoint, Point targetPoint);
    void updateRender();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

public:
    const double PI = 3.141592653589793238462643383279502;

protected:
    sf::RectangleShape line;
    sf::ConvexShape triangle;
    ColorButMulti colorButMulti;
    Point startPoint, targetPoint;

    double radiusTriangle;
    int lineWidth;
};

class Arrow : public ArrowShape {
public:
    Arrow(Point startPoint, Point targetPoint, int sizeLevel, const ColorButMulti& ColorButMulti);
    ~Arrow();

public:
    const int SIZELEVEL[6] = { 35, 25, 20, 15, 10 };

private:
    int sizeLevel;
    void setSizeLevel(int sizeLevel);
};

#endif