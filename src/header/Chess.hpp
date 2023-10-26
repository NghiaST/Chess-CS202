#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "include.hpp"
#include "Theme.hpp"
#include "PieceBoard.hpp"

class Chess {
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Sprite sprite;
    Theme* theme;
    
    void CreateGraphicsBoard();
    
public:
    Chess();
    ~Chess();
    void run();
};

#endif