#include <IngameScreen/PiecePrint.hpp>
#include <algorithm>

PiecePrint::PiecePrint(int index, int piece, int status)
    : Graphic(Point(0, 0), Point(0, 0), true, 0)
{
    this->isPrint = false;
    setIndex(index);
    setPiece(piece);
    setMouseStatus(MOUSE::None);
    this->status = status;
    this->isPrint = true;
    updateRender();
}

PiecePrint::~PiecePrint()
{
}

int PiecePrint::getPiece() const {
    return piece;
}
void PiecePrint::setPiece(int piece) {
    this->piece = piece;
    setIsPrint(piece != PIECE::None);
    updateRender();
}
void PiecePrint::setPiece(int pieceColor, int pieceType) {
    this->piece = pieceColor | pieceType;
    setIsPrint(piece != PIECE::None);
    updateRender();
}
void PiecePrint::setMouseStatus(int mousestatus, Point mousePosition)
{
    this->mousestatus = (MOUSE::STATUS) mousestatus;
    this->mousePosition = mousePosition;
    updateRender();
}
void PiecePrint::setIndex(int index)
{
    this->index = index;
    this->rank = index / 8;
    this->file = index % 8;
    updateRender();
}

void PiecePrint::updateRender() {
    if (!isPrint) return;
    double size_pBoard = renderSize.x;
    const sf::Texture& texture = Theme::getInstance()->getPieceTexture(piece);
    Point size = texture.getSize();
    if (size == Point(0, 0)) return;

    Point printPos;
    if (mousestatus != MOUSE::Hold) {
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

void PiecePrint::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!isPrint) return;
    target.draw(sprite, states);
}