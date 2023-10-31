#include "Piece.hpp"
#include <algorithm>

Piece::Piece(int position, CHESS::COLOR pieceColor, PIECE::TYPE pieceType, int status)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
    this->pieceColor = pieceColor;
    this->pieceType = pieceType;
    this->pieceData = pieceColor | pieceType;
    this->status = status;
    this->mousestatus = MOUSE::NONE;
    this->renderPosition = INTERFACE::POSBOARD;
}

Piece::Piece(int position, int pieceData, int status)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
    this->pieceColor = (CHESS::COLOR)(pieceData & CHESS::BLACKWHITE);
    this->pieceType = (PIECE::TYPE)(pieceData & 7);
    this->pieceData = pieceData;
    this->status = status;
    this->mousestatus = MOUSE::NONE;
    this->renderPosition = INTERFACE::POSBOARD;
}

Piece::~Piece()
{
}

const PIECE::TYPE& Piece::getPieceType() const {
    return pieceType;
}
const CHESS::COLOR& Piece::getPieceColor() const {
    return pieceColor;
}
const int& Piece::getPieceData() const {
    return pieceData;
}
void Piece::setPieceType(int pieceType) {
    setPiece(this->pieceColor, pieceType);
}
void Piece::setPieceColor(int pieceColor) {
    setPiece(pieceColor, this->pieceType);
}
void Piece::setPieceData(int pieceData) {
    setPiece(pieceData & CHESS::ALLCOLOR, pieceData & PIECE::ALLTYPE);
}
void Piece::setPiece(int pieceColor, int pieceType) {
    this->pieceColor = (CHESS::COLOR) pieceColor;
    this->pieceType = (PIECE::TYPE) pieceType;
    this->pieceData = pieceColor | pieceType;
}
void Piece::setMouseStatus(int mousestatus)
{
    this->mousestatus = (MOUSE::STATUS) mousestatus;
}
void Piece::setPosition(int position)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
}

void Piece::update(const Theme* theme) {
    double size_pBoard = renderSize.x;
    const sf::Texture& texture = theme->getPieceTexture(pieceData);
    sf::Vector2u size = texture.getSize();
    if (size == sf::Vector2u(0, 0)) return;

    int printPosx = renderPosition.x + posx * size_pBoard;
    int printPosy = renderPosition.y + (7 - posy) * size_pBoard;
    
    sprite.setTexture(texture);
    sprite.setScale(size_pBoard / size.x, size_pBoard / size.y);
    sprite.setPosition(printPosx, printPosy);
}

void Piece::render(sf::RenderTarget& target, sf::RenderStates state)
{
    target.draw(sprite);
}