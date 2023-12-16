#ifndef __Application_hpp__
#define __Application_hpp__

#include <Screen.hpp>
#include <DataControl/Include.hpp>
#include <DataControl/Theme.hpp>
#include <SFML/Graphics.hpp>

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    void changeScreen(ScreenType screenType);

private:
    sf::RenderWindow mWindow;
    Screen* mScreen;

    Point windowSize;
    Point windowPosition;
    sf::Clock clock;
};

#endif