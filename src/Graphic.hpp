#ifndef __Graphic_hpp__
#define __Graphic_hpp__
#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"

class Theme;
class Graphic {
protected:
    bool isPrint;
    int priorityPrint;
    Point windowPosition;
    sf::Sprite sprite;

public:
    Graphic(bool isPrint = true, int priorityPrint = 0, Point windowPosition = Point(0, 0));
    ~Graphic();
    void setPriorityPrint(int priorityPrint);
    void setWindowPosition(Point windowPosition);
    void setWindowPosition(double x, double y);
    const int& getPriorityPrint() const;
    virtual void preparePrint(const Theme* theme) = 0;
    virtual void print(sf::RenderWindow* window) = 0;
    // virtual void print(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) = 0;
};

#endif