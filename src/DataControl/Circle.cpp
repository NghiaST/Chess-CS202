#include "Circle.hpp"

Circle::Circle(Point renderPosition) 
    : Graphic(renderPosition, Point(64, 64), true, 100)
{
    this->colorButMulti = Color::ColorButMultiLight;
    this->thickness = -5;
    circleShape.setFillColor(sf::Color::Transparent);
    circleShape.setOutlineColor(colorButMulti.get(0).FillColor);
    circleShape.setOutlineThickness(thickness);
    circleShape.setRadius(renderSize.x / 2);
    circleShape.setPosition(renderPosition.to2f());
}

Circle::Circle(Point renderPosition, Point renderSize, float thickness, const ColorButMulti &colorButMulti)
    : Graphic(renderPosition, renderSize, true, 100)
{
    this->colorButMulti = colorButMulti;
    this->thickness = thickness;
    circleShape.setFillColor(sf::Color::Transparent);
    circleShape.setOutlineColor(colorButMulti.get(0).FillColor);
    circleShape.setOutlineThickness(thickness);
    circleShape.setRadius(renderSize.x / 2);
    circleShape.setPosition(renderPosition.to2f());
}

Circle::~Circle() {
}

void Circle::setOutlineThickness(float outlineThickness) {
    this->thickness = outlineThickness;
    circleShape.setOutlineThickness(outlineThickness);
}

void Circle::setColorBM(const ColorButMulti &colorButMulti) {
    this->colorButMulti = colorButMulti;
    circleShape.setOutlineColor(colorButMulti.get(0).FillColor);
}

void Circle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (isPrint) {
        target.draw(circleShape, states);
    }
}