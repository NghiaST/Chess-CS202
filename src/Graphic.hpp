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
public:
    Graphic(bool isPrint = true, int priorityPrint = 0, Point windowPosition = Point(0, 0));
    ~Graphic();
    void setPriorityPrint(int priorityPrint);
    void setWindowPosition(Point windowPosition);
    void setWindowPosition(double x, double y);
    void setIsPrint(bool isPrint);
    const int& getPriorityPrint() const;
    const Point& getWindowPosition() const;
    const bool& getIsPrint() const;
    virtual void update(const Theme* theme) = 0;
    virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) = 0;
};

#endif