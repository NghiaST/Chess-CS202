#ifndef __Graphic_hpp__
#define __Graphic_hpp__
#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"

class Theme;
class Graphic : public sf::Drawable {
public:
    Graphic(Point renderPosition = Point(0, 0), Point renderSize = Point(0, 0), bool isPrint = true, int priorityPrint = 0);
    void setPriorityPrint(int priorityPrint);
    void setRenderPosition(Point renderPosition);
    void setRenderPosition(double x, double y);
    void setRenderSize(Point renderSize);
    void setIsPrint(bool isPrint);
    const int& getPriorityPrint() const;
    const Point& getRenderPosition() const;
    bool getIsPrint() const;
    bool isMouseOn(Point mousePos) const;

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;

protected:
    bool isPrint;
    int priorityPrint;
    Point renderPosition;
    Point renderSize;
};

#endif