#include "main.hpp"
#include "Chess.hpp"
#include <SFML/Graphics.hpp>

int main()
{/*
    Theme* theme = new Theme();
    sf::RenderWindow window(sf::VideoMode(700, 700), "ChessLion");
    window.clear(sf::Color::Yellow);
    
    sf::Texture texture = theme->getPieceTexture(9);
    // texture.loadFromFile("img.jpg");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    window.draw(sprite);

    Piece* piece = new Piece(8, 9);
    piece->preparePrint(theme);
    piece->print(&window);


    window.display();
    system("pause");

 return 0;*/

    Chess* chess = new Chess();
    chess->run();
    delete chess;
    return 0;
}