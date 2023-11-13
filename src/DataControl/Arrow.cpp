#include "Arrow.hpp"
#include <cmath>

ArrowShape::ArrowShape() {
}

ArrowShape::ArrowShape(Point startPoint, Point targetPoint, const ColorButMulti& colorButMulti, int radiusTriangle, int lineWidth) {
    this->startPoint = startPoint;
    this->targetPoint = targetPoint;
    this->colorButMulti = colorButMulti;
    this->radiusTriangle = radiusTriangle;
    this->lineWidth = lineWidth;
    updateRender();
}

ArrowShape::~ArrowShape() {}

void ArrowShape::setColorBM(ColorButMulti colorButMulti) {
    this->colorButMulti = colorButMulti;
    updateRender();
}

void ArrowShape::setRadiusTriangle(int radiusTriangle) {
    this->radiusTriangle = radiusTriangle;
    updateRender();
}

void ArrowShape::setLineWidth(int lineWidth) {
    this->lineWidth = lineWidth;
    updateRender();
}

void ArrowShape::setArrowPosition(Point startPoint, Point targetPoint) {
    this->startPoint = startPoint;
    this->targetPoint = targetPoint;
    updateRender();
}

void ArrowShape::updateRender()
{
    Point diff = targetPoint - startPoint;
    double maxLength = sqrt(diff.x * diff.x + diff.y * diff.y);
    double lengthLine = sqrt(diff.x * diff.x + diff.y * diff.y) - radiusTriangle * 1.3333;
    double rad = atan2(diff.y, diff.x);

    Point PointCenter = targetPoint - Point(cos(rad), sin(rad)) * radiusTriangle;
    Point Point_p1 = targetPoint;
    Point Point_p2 = PointCenter + Point(cos(rad + PI * 2 / 3), sin(rad + PI * 2 / 3)) * radiusTriangle;
    Point Point_p3 = PointCenter + Point(cos(rad - PI * 2 / 3), sin(rad - PI * 2 / 3)) * radiusTriangle;

    triangle.setPointCount(3);
    triangle.setPoint(0, Point_p1.to2f());
    triangle.setPoint(1, Point_p2.to2f());
    triangle.setPoint(2, Point_p3.to2f());

    line.setSize(sf::Vector2f(lengthLine, lineWidth));
    line.setOrigin(0, lineWidth / 2);
    line.setPosition(startPoint.to2f());
    line.setRotation(rad * 180 / PI);
    line.setOutlineThickness(0);
    line.setFillColor(colorButMulti.get(0).FillColor);

    triangle.setOutlineThickness(0);
    triangle.setFillColor(colorButMulti.get(0).FillColor);
}

void ArrowShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(line, states);
    target.draw(triangle, states);
}

Arrow::Arrow(Point startPoint, Point targetPoint, int sizeLevel, const ColorButMulti& colorButMulti)
    : ArrowShape(startPoint, targetPoint, colorButMulti, 0, 0) 
{
    setSizeLevel(sizeLevel);
}

Arrow::~Arrow() {}

void Arrow::setSizeLevel(int sizeLevel) {
    this->sizeLevel = sizeLevel;
    setRadiusTriangle(SIZELEVEL[sizeLevel]);
    setLineWidth(SIZELEVEL[sizeLevel]);
}