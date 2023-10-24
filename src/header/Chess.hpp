#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

// struct Piece;
// struct Board;
// struct Pawn;

struct Chess {
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Color myColor;
    void CreateGraphicsBoard();
    
public:
    Chess();
    ~Chess();
    void run();
};

#endif