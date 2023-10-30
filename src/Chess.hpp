#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"
#include "DataControl/Theme.hpp"
#include "BoardScreen/PieceBoard.hpp"

class Chess {
private:
    PieceBoard* pieceBoard;
    sf::RenderWindow mWindow;
private:
    Point windowSize;
    sf::Vector2i renderPosition;
    sf::Clock clock;

public:
    Chess();
    ~Chess();
    void run();

private:
    void processEvents();
    void update();
    void render();
    
};

#endif