#include <IngameScreen/PiecePrint.hpp>
#include <algorithm>

PiecePrint::PiecePrint()
    : ImageActive()
{
    setIsPrint(false);
    setIndex(56);
    setPiece(PIECE::None);
    setMouseStatus(MOUSE::STATUS::None);
}

PiecePrint::PiecePrint(int index, int piece, int status)
    : ImageActive()
{
    setIsPrint(true);
    setIndex(index);
    setPiece(piece);
    setMouseStatus(status);
}

PiecePrint::PiecePrint(Point boardPosition, Point renderSize, int index, int piece, int status)
    : ImageActive()
{
    setIsPrint(true);
    setRenderSize(renderSize);
    setIndex(index);
    setPiece(piece);
    setBoardPosition(boardPosition);
    setMouseStatus(status);
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
    setTexture(Theme::getInstance()->getPieceTexture(piece));
    updatePosition();
}
void PiecePrint::setPiece(int pieceColor, int pieceType) {
    setPiece(pieceColor | pieceType);
}
void PiecePrint::setIndex(int index) {
    this->index = index;
    this->rank = index / 8;
    this->file = index % 8;
    updatePosition();
}
void PiecePrint::setBoardPosition(Point boardPosition) {
    this->boardPosition = boardPosition;
    updatePosition();
}

void PiecePrint::updatePosition() {
    Point newmPosition;
    newmPosition.x = boardPosition.x + file * renderSize.x;
    newmPosition.y = boardPosition.y + (7 - rank) * renderSize.y;
    setMainPosition(newmPosition);
}