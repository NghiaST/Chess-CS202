#include "Graphic.hpp"

// Graphic::Graphic(sf::RenderWindow*& window, const Theme* theme, int priorityPrint, Point windowPosition)
// {
//     this->window = window;
//     this->theme = theme;
//     this->priorityPrint = priorityPrint;
//     this->windowPosition = windowPosition;
// }

// void Graphic::setWindow(sf::RenderWindow*& window)
// {
//     this->window = window;
// }

// void Graphic::setTheme(const Theme *theme)
// {
//     this->theme = theme;
//     reloadTheme();
// }

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

const int& Graphic::getPriorityPrint() const {
    return priorityPrint;
}

