#ifndef __Graphic_hpp__
#define __Graphic_hpp__
#include <SFML/Graphics.hpp>
#include "include.hpp"

class Theme;
class Graphic {
protected:
    // sf::RenderWindow* window;
    // const Theme* theme;
    bool isPrint;
    int priorityPrint;
    Point windowPosition;
    sf::Sprite sprite;

public:
    Graphic(bool isPrint = true, int priorityPrint = 0, Point windowPosition = Point(0, 0));
    ~Graphic();
    // Graphic(sf::RenderWindow*& window, const Theme* theme, int priorityPrint, Point windowPosition);
    // void setWindow(sf::RenderWindow*& window);
    // void setTheme(const Theme* theme);
    void setPriorityPrint(int priorityPrint);
    void setWindowPosition(Point windowPosition);
    void setWindowPosition(double x, double y);
    const int& getPriorityPrint() const;
    // virtual void reloadTheme() = 0;
    virtual void preparePrint(const Theme* theme) = 0;
    virtual void print(sf::RenderWindow* window) = 0;
};

#endif