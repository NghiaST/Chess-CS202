#include "BoardPrint.hpp"

BoardPrint::BoardPrint(Point boardPosition, Point boardSize) 
  : Graphic(boardPosition, boardSize, true, 100)
{
    stateBoard.resize(64);
    for(int i = 0; i < 64; i++) {
        stateBoard[i] = i % 6;
    }
}

BoardPrint::~BoardPrint() {
}

void BoardPrint::setStateBoard(const std::vector<int>& stateBoard) {
    this->stateBoard = stateBoard;
}

void BoardPrint::setStateCell(int index, int state) {
    this->stateBoard[index] = state;
}

int BoardPrint::getStateCell(int index)
{
    return this->stateBoard[index];
}

void BoardPrint::update(const Theme* theme) {
    Point cellSize = renderSize / 8;
    spriteBoardList.clear();
    spriteBoardShaderList.clear();
    const sf::Texture& boardTexture = theme->getBoardTexture();
    const sf::Texture& boardSelectedTexture = theme->getBoardSelectedTexture();
    const sf::Texture& boardPreMoveTexture = theme->getBoardPreMoveTexture();
    const sf::Texture& boardMoveTexture = theme->getBoardMoveTexture();
    const sf::Texture& boardCaptureTexture = theme->getBoardCaptureTexture();
    const sf::Texture& boardCheckTexture = theme->getBoardCheckTexture();
    const sf::Texture& boardCheckMateTexture = theme->getBoardCheckMateTexture();

    // if no texture, return
    sf::Vector2u size = boardTexture.getSize();
    sf::Vector2u sizeOther = boardSelectedTexture.getSize();
    if (size == sf::Vector2u(0, 0)) return;

    // calculate size and position of square
    {
        sf::Sprite sprite;
        sprite.setTexture(boardTexture);
        
        sprite.setScale(renderSize.x / size.x, renderSize.y / size.y);
        sprite.setPosition(renderPosition.to2f());
        spriteBoardList.push_back(sprite);
    }

    for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++) {
        int index = i * 8 + j;
        int color = (i+j) % 2;
        
        float printPosx = renderPosition.x + i * cellSize.x;
        float printPosy = renderPosition.y + (7 - j) * cellSize.y;

        // add boardPrint, common
        if (false) {
            sf::Sprite sprite;
            sprite.setTexture(boardTexture);
            sprite.setTextureRect(sf::IntRect(color * size.x / 2, 0, size.x / 2, size.y));
            
            sprite.setScale(cellSize.x / size.x * 2, cellSize.y / size.y);
            sprite.setPosition(printPosx, printPosy);
            spriteBoardList.push_back(sprite);
        }

        // add boardPrint if state is: selected, move, capture, check, checkmate
        if (stateBoard[index]) {
            sf::Sprite sprite;
            switch(stateBoard[index]) {
                case STATUS::SELECTED:
                    sprite.setTexture(boardSelectedTexture);
                    break;
                case STATUS::PREMOVE:
                    sprite.setTexture(boardPreMoveTexture);
                    break;
                case STATUS::POSSIBLE:
                    sprite.setTexture(boardMoveTexture);
                    break;
                case STATUS::CHECK:
                    sprite.setTexture(boardCheckTexture);
                    break;
                case STATUS::CHECKMATE:
                    sprite.setTexture(boardCheckMateTexture);
                    break;
                default:
                    sprite.setTexture(boardSelectedTexture);
                    break;
            }
            sprite.setScale(cellSize.x / sizeOther.x, cellSize.y / sizeOther.y);
            sprite.setPosition(printPosx, printPosy);
            spriteBoardShaderList.push_back(sprite);
        }
    }
}

void BoardPrint::render(sf::RenderTarget& target, sf::RenderStates state) const {
    for(sf::Sprite sprite : spriteBoardList) {
        target.draw(sprite);
    }
    for(sf::Sprite sprite : spriteBoardShaderList) {
        target.draw(sprite, state);
    }
}