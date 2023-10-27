#include "Board.hpp"

Board::Board() {
    this->priorityPrint = 100;
    this->windowPosition = INTERFACE::POSBOARD;
    this->textureList.resize(2);
}

Board::~Board() {
}

void Board::preparePrint(const Theme* theme) {
    double size_board = INTERFACE::SIZEBOARD;
    spriteSquareList.clear();
    const sf::Texture& texture = theme->getBoardTexture();
    sf::Vector2u size = texture.getSize();
    if (size == sf::Vector2u(0, 0)) return;

    for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++) {
        int index = i * 8 + j;
        int color = (i+j) % 2;
        
        int printPosx = windowPosition.x + i * size_board;
        int printPosy = windowPosition.y + (7 - j) * size_board;

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(color * size.x / 2, 0, size.x / 2, size.y));
        
        sprite.setScale(size_board / size.x * 2, size_board / size.y);
        sprite.setPosition(printPosx, printPosy);
        spriteSquareList.push_back(sprite);
    }
}

void Board::print(sf::RenderWindow* window) {
    for(int i = 0; i < 64; i++) {
        window->draw(spriteSquareList[i]);
    }
}