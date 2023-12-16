#include <DataControl/ButtonPiece.hpp>

ButtonPiece::ButtonPiece(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin,
    const sf::Font* sfFont, const ColorButMulti& colorButMulti, float thickness)
{
    renderPosition = renderPosition - renderSize / 2 * isPositionCenter;
    button = new Button(buttonID, renderPosition, renderSize, false, isRenderTextOrigin, sfFont, colorButMulti, 12, "", thickness);
    image = new PiecePrint(renderPosition, renderSize, 56, buttonID, 0);
}

ButtonPiece::~ButtonPiece() {
    delete button;
    delete image;
}

void ButtonPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*button, states);
    target.draw(*image, states);
}

// Accessors
Button* ButtonPiece::getButton() {
    return button;
}

PiecePrint* ButtonPiece::getImage() {
    return image;
}

int ButtonPiece::getButtonID() const {
    return button->getButtonID();
}

const ColorButMulti& ButtonPiece::getColorButMulti() const {
    return button->getColorBM();
}

int ButtonPiece::getButtonState() const {
    return button->getButtonState();
}

// Mutators
void ButtonPiece::TurnPiece(bool isTurnOn) {
    button->setButtonState(isTurnOn ? ButtonStates::BTN_ACTIVE : ButtonStates::BTN_IDLE);
    image->setMouseStatus(isTurnOn ? MOUSE::Hold : MOUSE::None);
}

void ButtonPiece::setColorBM(const ColorButMulti& colorButMulti) {
    button->setColorBM(colorButMulti);
}

void ButtonPiece::setMainPosition(Point renderPosition) {
    button->setRenderPosition(renderPosition);
    image->setMainPosition(renderPosition);
}

void ButtonPiece::setRenderSize(Point renderSize) {
    button->setRenderSize(renderSize);
    image->setRenderSize(renderSize);
}

bool ButtonPiece::handleEvent(const sf::Event &event) {
    button->handleEvent(event);
    image->handleEvent(event);
    if (button->getButtonState() == ButtonStates::BTN_ACTIVE) {
        image->setMouseStatus(MOUSE::Hold);
    }
    if (button->isReleased()) {
        image->setMouseStatus(MOUSE::None);
        button->setIsReleased(false);
        return true;
    }
    return false;
}