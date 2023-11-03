#include "Piece.hpp"
#include <algorithm>

Piece::Piece(int position, CHESS::COLOR pieceColor, PIECE::TYPE pieceType, int status)
    : Graphic(Point(0, 0), Point(0, 0), true, 0)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
    setPiece(pieceColor, pieceType);
    this->status = status;
    this->mousestatus = MOUSE::NONE;
}

Piece::Piece(int position, int pieceData, int status)
    : Graphic(Point(0, 0), Point(0, 0), true, 0)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
    setPieceData(pieceData);
    this->status = status;
    this->mousestatus = MOUSE::NONE;
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
    setPiece(pieceData & CHESS::BOTHCOLOR, pieceData & PIECE::ALLTYPE);
}
void Piece::setPiece(int pieceColor, int pieceType) {
    this->pieceColor = (CHESS::COLOR) pieceColor;
    this->pieceType = (PIECE::TYPE) pieceType;
    this->pieceData = pieceColor | pieceType;
    setIsPrint(pieceData != PIECE::NONE);
}
void Piece::setMouseStatus(int mousestatus, Point mousePosition)
{
    this->mousestatus = (MOUSE::STATUS) mousestatus;
    this->mousePosition = mousePosition;
}
void Piece::setPosition(int position)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
}

void Piece::update(const Theme* theme) {
    if (!isPrint) return;
    double size_pBoard = renderSize.x;
    const sf::Texture& texture = theme->getPieceTexture(pieceData);
    Point size = texture.getSize();
    if (size == Point(0, 0)) return;

    Point printPos;
    if (mousestatus != MOUSE::HOLD) {
        printPos.x = renderPosition.x + posx * size_pBoard;
        printPos.y = renderPosition.y + (7 - posy) * size_pBoard;
        setPriorityPrint(1);
    }
    else {
        printPos = mousePosition - renderSize / 2;
        setPriorityPrint(100);
    }

    sprite.setTexture(texture);
    sprite.setScale(size_pBoard / size.x, size_pBoard / size.y);
    sprite.setPosition(printPos.x, printPos.y);
}

void Piece::render(sf::RenderTarget& target, sf::RenderStates state) const
{
    if (!isPrint) return;
    target.draw(sprite);
}