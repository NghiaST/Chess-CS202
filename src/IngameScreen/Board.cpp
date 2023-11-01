#include "Board.hpp"

Board::Board() 
  : Graphic(INTERFACE::POSBOARD, Point(60, 60), true, 100)
{
    stateBoard.resize(64);
    for(int i = 0; i < 64; i++) {
        stateBoard[i] = i % 6;
    }
}

Board::~Board() {
}

void Board::setStateBoard(const std::vector<int>& stateBoard) {
    this->stateBoard = stateBoard;
}

void Board::setStateCell(int index, int state) {
    this->stateBoard[index] = state;
}

int Board::getStateCell(int index)
{
    return this->stateBoard[index];
}

void Board::update(const Theme* theme) {
    double sizeBoard = renderSize.x / 8;
    spriteBoardList.clear();
    spriteBoardShaderList.clear();
    const sf::Texture& boardTexture = theme->getBoardTexture();
    const sf::Texture& boardSelectedTexture = theme->getBoardSelectedTexture();
    const sf::Texture& boardMoveTexture = theme->getBoardMoveTexture();
    const sf::Texture& boardCaptureTexture = theme->getBoardCaptureTexture();
    const sf::Texture& boardCheckTexture = theme->getBoardCheckTexture();
    const sf::Texture& boardCheckMateTexture = theme->getBoardCheckMateTexture();

    // if no texture, return
    sf::Vector2u size = boardTexture.getSize();
    sf::Vector2u sizeOther = boardSelectedTexture.getSize();
    if (size == sf::Vector2u(0, 0)) return;

    // calculate size and position of square
    for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++) {
        int index = i * 8 + j;
        int color = (i+j) % 2;
        
        int printPosx = renderPosition.x + i * sizeBoard;
        int printPosy = renderPosition.y + (7 - j) * sizeBoard;

        // add board, common
        {
            sf::Sprite sprite;
            sprite.setTexture(boardTexture);
            sprite.setTextureRect(sf::IntRect(color * size.x / 2, 0, size.x / 2, size.y));
            
            sprite.setScale(sizeBoard / size.x * 2, sizeBoard / size.y);
            sprite.setPosition(printPosx, printPosy);
            spriteBoardList.push_back(sprite);
        }

        // add board if state is: selected, move, capture, check, checkmate
        if (stateBoard[index]) {
            sf::Sprite sprite;
            switch(stateBoard[index]) {
                case 1:
                    sprite.setTexture(boardSelectedTexture);
                    break;
                case 2:
                    sprite.setTexture(boardMoveTexture);
                    break;
                case 3:
                    sprite.setTexture(boardCaptureTexture);
                    break;
                case 4:
                    sprite.setTexture(boardCheckTexture);
                    break;
                case 5:
                    sprite.setTexture(boardCheckMateTexture);
                    break;
                default:
                    break;
            }
            sprite.setScale(sizeBoard / sizeOther.x, sizeBoard / sizeOther.y);
            sprite.setPosition(printPosx, printPosy);
            spriteBoardShaderList.push_back(sprite);
        }
    }
}

void Board::render(sf::RenderTarget& target, sf::RenderStates state) const {
    for(sf::Sprite sprite : spriteBoardList) {
        target.draw(sprite);
    }
    for(sf::Sprite sprite : spriteBoardShaderList) {
        target.draw(sprite, state);
    }
}