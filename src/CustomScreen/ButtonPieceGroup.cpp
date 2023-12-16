#include <CustomScreen/ButtonPieceGroup.hpp>

ButtonPieceGroup::ButtonPieceGroup(Point renderPosition) {
    this->pieceReleased = 0;

    Point renderSize = Point(398, 154);
    Point titalPosition = renderPosition;

    Point pieceSize = Point(64, 64);

    Theme* theme = Theme::getInstance();
    title = new Button(0, titalPosition, renderSize, false, true, &theme->getFont(), theme->getColorStatic(), 15, "Pieces", 0, Point(0, -renderSize.y / 2 + 10));
    
    Point rootRenderPosition = renderPosition + Point(0, 20);
    for(int color = 1; color <= 2; color++) {
        for(int type = 1; type <= 6; type++) {
            int piece = color * 8 + type;
            Point curPosition = rootRenderPosition + Point((type - 1) * pieceSize.x, (color - 1) * pieceSize.y) + Point(type, color) * 2;
            buttonPieceList.push_back(new ButtonPiece(piece, curPosition, pieceSize, false, true, &theme->getFont(), theme->getColorDefault(), -1));
        }
    }
}

ButtonPieceGroup::~ButtonPieceGroup() {
    delete title;
    for(auto buttonPiece : buttonPieceList) {
        delete buttonPiece;
    }
}

bool ButtonPieceGroup::isPieceReleased() const {
    return pieceReleased != 0;
}

int ButtonPieceGroup::getPieceReleased() const {
    return pieceReleased;
}

void ButtonPieceGroup::TurnOnPiece(int piece) {
    int index = (piece / 8) * 6 + piece % 8 - 7;
    buttonPieceList[index]->TurnPiece(true);
}

bool ButtonPieceGroup::handleEvent(const sf::Event& event) {
    pieceReleased = PIECE::None;
    bool ret = false;
    title->handleEvent(event);
    for(auto buttonPiece : buttonPieceList) {
        if(buttonPiece->handleEvent(event)) {
            pieceReleased = buttonPiece->getImage()->getPiece();
            ret = true;
        }
    }
    return ret;
}

void ButtonPieceGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*title, states);
    for(auto buttonPiece : buttonPieceList) {
        target.draw(*buttonPiece, states);
    }
}