#ifndef __FrontEnd_hpp__
#define __FrontEnd_hpp__

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Theme.hpp"

class Chess;

class FrontEnd {
private:
    sf::RenderWindow* window;
    Theme* theme;
    Point windowSize;
    Point mousePos;
    int mouseStatus; // 0: none, 1: clicked, 2: pressed, 3: unclicked
    double timeMousePress;
private:
    sf::Clock clock;
public:
    const Point& _windowSize = windowSize;
    const Point& _mousePos = mousePos;
    const int& _mouseStatus = mouseStatus;
    const double& _timeMousePress = timeMousePress;
    const Theme* const _theme = theme;

public:
    FrontEnd();
    ~FrontEnd();

    void setTheme(const ThemeIndex themeIndex);
    void setMouseStatus(int mouseStatus);
    void setMousePos(int x, int y);
    void setMousePos(Point mousePos);
    void setWindowSize(int windowWidth, int windowHeight);
    void setWindow(sf::RenderWindow* window);
    void setTimeMousePress(double timeMousePress);
    const Point& getMousePos() const;
    const Theme* getTheme() const;
    sf::RenderWindow* getWindow() const;

    bool isRunning() const;
    void processEvents();
    void print();
};

#endif