#include "Piece.hpp"
#include <algorithm>

Piece::Piece(int index, int piece, int status)
    : Graphic(Point(0, 0), Point(0, 0), true, 0)
{
    setIndex(index);
    setPiece(piece);
    setMouseStatus(MOUSE::NONE);
    this->status = status;
}

Piece::~Piece()
{
}

const int Piece::getPiece() const {
    return piece;
}
void Piece::setPiece(int piece) {
    this->piece = piece;
    setIsPrint(piece != PIECE::None);
}
void Piece::setPiece(int pieceColor, int pieceType) {
    this->piece = pieceColor | pieceType;
    setIsPrint(piece != PIECE::None);
}
void Piece::setMouseStatus(int mousestatus, Point mousePosition)
{
    this->mousestatus = (MOUSE::STATUS) mousestatus;
    this->mousePosition = mousePosition;
}
void Piece::setIndex(int index)
{
    this->index = index;
    this->rank = index / 8;
    this->file = index % 8;
}

void Piece::update(const Theme* theme) {
    if (!isPrint) return;
    double size_pBoard = renderSize.x;
    const sf::Texture& texture = theme->getPieceTexture(piece);
    Point size = texture.getSize();
    if (size == Point(0, 0)) return;

    Point printPos;
    if (mousestatus != MOUSE::HOLD) {
        printPos.x = renderPosition.x + file * size_pBoard;
        printPos.y = renderPosition.y + (7 - rank) * size_pBoard;
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