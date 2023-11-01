#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"
#include "DataControl/Theme.hpp"
#include "IngameScreen/IngameScreen.hpp"

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
    sf::RenderWindow mWindow;
    IngameScreen* pieceBoard;

    Point windowSize;
    Point renderPosition;
    sf::Clock clock;
};

#endif