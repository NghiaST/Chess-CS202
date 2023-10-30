#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"
#include "DataControl/Theme.hpp"
#include "DataControl/Event.hpp"
#include "BoardScreen/PieceBoard.hpp"

class Chess {
private:
    Event* event;
    PieceBoard* pieceBoard;
    sf::RenderWindow mWindow;
private:
    Point windowSize;
    sf::Vector2i windowPosition;

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