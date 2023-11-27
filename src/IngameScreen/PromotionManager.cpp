#include <IngameScreen/PromotionManager.hpp>

PromotionManager::PromotionManager(int id, Point renderPosition, Point renderSize)
    : Graphic(renderPosition, renderSize, false, 100)
{
    Point squareSize = renderSize / 8;
    pieceType = std::vector<int>{PIECE::Queen, PIECE::Rook, PIECE::Bishop, PIECE::Knight};
    for(int i = 0; i < 4; i++) {
        pieces.push_back(PiecePrint(renderPosition, squareSize, 0, pieceType[i] | PIECE::White));
    }
    buttonPieces.assign(4, nullptr);

    Theme* theme = Theme::getInstance();
    for(Button* &button : buttonPieces) {
        button = new Button(id, Point(), squareSize, false, true, &theme->getFont(), theme->getColorDefault(), 20, "");
    }
    isWhite = true;
    isRotate = false;
    setPromotionFile(-1);
}

PromotionManager::~PromotionManager() {}

bool PromotionManager::handleEvent(const sf::Event &event) {
    if (!isPrint) return false;
    for(int i = 0; i < 4; i++) {
        if (buttonPieces[i]->handleEvent(event)) {
            isClicked = true;
            pieceClicked = i;
            buttonPieces[i]->setButtonState(BTN_IDLE);
            return true;
        }
    }
    return false;
}

void PromotionManager::setPromotionFile(int promotionFile)
{
    this->promotionFile = promotionFile;
    isPrint = (promotionFile != -1);
    isClicked = false;
    updateRender();
}

void PromotionManager::setIsWhite(bool isWhite) {
    this->isWhite = isWhite;
    updateRender();
}

void PromotionManager::setIsRotate(bool isRotate) {
    this->isRotate = isRotate;
    updateRender();
}

void PromotionManager::updateRender() {
    if (!isPrint) return;
    Point squareSize = renderSize / 8;
    int index = isWhite ? 56 + promotionFile : promotionFile;
    int indexMove = isWhite ? -8 : 8;
    if (isRotate) {
        index = 63 - index;
        indexMove *= -1;
    }

    for(int i = 0; i < 4; i++) {
        int curIndex = index + indexMove * i;
        Point offsetImg = Point(curIndex % 8, 7 - curIndex / 8);
        Point squarePosition = renderPosition + Point(squareSize.x * offsetImg.x, squareSize.y * offsetImg.y);
        pieces[i].setIndex(curIndex);
        pieces[i].setPiece(pieceType[i] | PIECE::boolToColor(isWhite));
        buttonPieces[i]->setRenderSize(squareSize);
        buttonPieces[i]->setRenderPosition(squarePosition);
    }
}

int PromotionManager::getPiecePromotionType() const {
    if (!isPrint) return 0;
    if (!isClicked) return 0;
    return pieceType[pieceClicked];
}

void PromotionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!isPrint) return;
    for(int i = 0; i < 4; i++) {
        target.draw(*buttonPieces[i], states);
        target.draw(pieces[i], states);
    }
}