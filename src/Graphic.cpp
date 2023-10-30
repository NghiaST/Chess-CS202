#include "Graphic.hpp"

Graphic::Graphic(bool isPrint, int priorityPrint, Point windowPosition)
{
    this->isPrint = isPrint;
    this->priorityPrint = priorityPrint;
    this->windowPosition = windowPosition;
}

Graphic::~Graphic()
{
}

void Graphic::setPriorityPrint(int priorityPrint)
{
    this->priorityPrint = priorityPrint;
}

void Graphic::setWindowPosition(Point windowPosition)
{
    this->windowPosition = windowPosition;
}

void Graphic::setWindowPosition(double x, double y) {
    this->windowPosition = Point(x, y);
}

void Graphic::setIsPrint(bool isPrint) {
    this->isPrint = isPrint;
}

const int& Graphic::getPriorityPrint() const {
    return priorityPrint;
}

const Point& Graphic::getWindowPosition() const {
    return windowPosition;
}

const bool& Graphic::getIsPrint() const {
    return isPrint;
}
