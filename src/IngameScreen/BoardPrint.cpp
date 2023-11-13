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

void BoardPrint::setStateCell(int index, STATUS state) {
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
    const TextureBoard& textureBoard = theme->getTextureBoard();

    // if no texture, return
    sf::Vector2u size = textureBoard.getTexture(TextureBoard::Board).getSize();
    sf::Vector2u sizeCell = textureBoard.getTexture(TextureBoard::Selected).getSize();
    if (size == sf::Vector2u(0, 0)) return;

    // calculate size and index of square
    {
        sf::Sprite sprite;
        sprite.setTexture(textureBoard.getTexture(TextureBoard::Board));
        
        sprite.setScale(renderSize.x / size.x, renderSize.y / size.y);
        sprite.setPosition(renderPosition.to2f());
        spriteBoardList.push_back(sprite);
    }

    for(int rank = 0; rank < 8; rank++)
    for(int file = 0; file < 8; file++) {
        int index = rank * 8 + file;
        int colorBoard = (rank + file) % 2;
        
        float printPosx = renderPosition.x + file * cellSize.x;
        float printPosy = renderPosition.y + (7 - rank) * cellSize.y;

        if (stateBoard[index]) {
            sf::Sprite sprite;
            switch(stateBoard[index]) {
                case STATUS::Selected:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::Selected));
                    break;
                case STATUS::Hover:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::Hover));
                    break;
                case STATUS::PreMoveStart:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::PreMoveStart));
                    break;
                case STATUS::PreMoveTarget:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::PreMoveTarget));
                    break;
                case STATUS::Possible:  
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::Possible));
                    break;
                case STATUS::PossibleCapture:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::PossibleCapture));
                    break;
                case STATUS::Check:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::Check));
                    break;
                case STATUS::CheckMate:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::CheckMate));
                    break;
                case STATUS::StaleMate:
                    sprite.setTexture(textureBoard.getTexture(TextureBoard::StaleMate));
                    break;
                default:
                    break;
            }
            sprite.setScale(cellSize.x / sizeCell.x, cellSize.y / sizeCell.y);
            sprite.setPosition(printPosx, printPosy);
            spriteBoardShaderList.push_back(sprite);
        }
    }
}

void BoardPrint::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(sf::Sprite sprite : spriteBoardList) {
        target.draw(sprite);
    }
    for(sf::Sprite sprite : spriteBoardShaderList) {
        target.draw(sprite, states);
    }
}