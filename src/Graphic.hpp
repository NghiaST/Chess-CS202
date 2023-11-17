#ifndef __Graphic_hpp__
#define __Graphic_hpp__

#include "DataControl/Point.hpp"
#include "DataControl/RenderPS.hpp"
#include <SFML/Graphics.hpp>

class Graphic : public sf::Drawable {
public:
    Graphic(Point renderPosition = Point(0, 0), Point renderSize = Point(0, 0), bool isPrint = true, int priorityPrint = 0);
    Graphic(RenderPS renderPS, bool isPrint = true, int priorityPrint = 0);
    
    // Mutators
    void setPriorityPrint(int priorityPrint);
    virtual void setRenderPosition(Point renderPosition);
    virtual void setRenderPosition(double x, double y);
    virtual void setRenderSize(Point renderSize);
    void setIsPrint(bool isPrint);

    // Accessors
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