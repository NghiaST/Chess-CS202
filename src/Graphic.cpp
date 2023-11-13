#include "Graphic.hpp"

Graphic::Graphic(Point renderPosition, Point renderSize, bool isPrint, int priorityPrint)
{
    this->renderPosition = renderPosition;
    this->renderSize = renderSize;
    this->isPrint = isPrint;
    this->priorityPrint = priorityPrint;
}

void Graphic::setPriorityPrint(int priorityPrint)
{
    this->priorityPrint = priorityPrint;
}

void Graphic::setRenderPosition(Point renderPosition)
{
    this->renderPosition = renderPosition;
}

void Graphic::setRenderPosition(double x, double y) {
    this->renderPosition = Point(x, y);
}

void Graphic::setRenderSize(Point renderSize) {
    this->renderSize = renderSize;
}

void Graphic::setIsPrint(bool isPrint) {
    this->isPrint = isPrint;
}

const int& Graphic::getPriorityPrint() const {
    return priorityPrint;
}

const Point& Graphic::getRenderPosition() const {
    return renderPosition;
}

bool Graphic::getIsPrint() const {
    return isPrint;
}

bool Graphic::isMouseOn(Point mousePos) const {
    return (mousePos.x >= renderPosition.x && mousePos.x < renderPosition.x + renderSize.x && mousePos.y >= renderPosition.y && mousePos.y < renderPosition.y + renderSize.y);
}