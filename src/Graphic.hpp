#ifndef __Graphic_hpp__
#define __Graphic_hpp__
#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"

class Theme;
class Graphic {
protected:
    bool isPrint;
    int priorityPrint;
    Point renderPosition;
    Point renderSize;
public:
    Graphic(bool isPrint = true, int priorityPrint = 0, Point renderPosition = Point(0, 0), Point renderSize = Point(0, 0));
    ~Graphic();
    void setPriorityPrint(int priorityPrint);
    void setRenderPosition(Point renderPosition);
    void setRenderPosition(double x, double y);
    void setRenderSize(Point renderSize);
    void setIsPrint(bool isPrint);
    const int& getPriorityPrint() const;
    const Point& getrenderPosition() const;
    bool getIsPrint() const;
    bool isMouseOn(Point mousePos) const;
    
    virtual void update(const Theme* theme) = 0;
    virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) = 0;
};

#endif