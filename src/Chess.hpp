#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"
#include "DataControl/Theme.hpp"
#include "IngameScreen/IngameScreen.hpp"
#include "HomeScreen/HomeScreen.hpp"

class Chess {
public:
    Chess();
    ~Chess();
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
    IngameScreen* ingameScreen;
    HomeScreen* homeScreen;

    Point windowSize;
    Point renderPosition;
    sf::Clock clock;
};

#endif