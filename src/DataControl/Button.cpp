#include <DataControl/Button.hpp>

Button::Button(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
        const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText, 
        std::string text, float thickness, Point renderOffsetText)
    : TextBox(buttonID, renderPosition, renderSize, isPositionCenter, isRenderTextOrigin, 
            sfFont, Color::ButtonDefault, sizeText, text, thickness, renderOffsetText)
{
    this->colorButMulti = colorButMulti;
    setButtonState(BTN_IDLE);
    mIsReleased = false;
}

Button::~Button() {
}

// Mutators
void Button::setButtonState(ButtonStates buttonState) {
    this->buttonState = buttonState;
    setColorButton(colorButMulti.get((int) buttonState));
}

void Button::setColorBM(const ColorButMulti &colorButMulti) {
    this->colorButMulti = colorButMulti;
    setColorButton(colorButMulti.get((int) buttonState));
}

void Button::setIsReleased(bool mIsReleased) {
    this->mIsReleased = mIsReleased;
}

// Accessors
int Button::getButtonState() const {
    return this->buttonState;
}

const ColorButMulti &Button::getColorBM() const {
    return this->colorButMulti;
}

bool Button::isReleased() const {
    return mIsReleased;
}

//Functions
bool Button::handleEvent(const sf::Event& event) {
    bool mIsEvent = false;
    if (event.type == sf::Event::MouseButtonPressed) {
        Point mousePos = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOn(mousePos)) {
                setButtonState(BTN_ACTIVE);
                mIsEvent = true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        Point mousePos = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (buttonState == BTN_ACTIVE)
                mIsReleased = true;
            if (isMouseOn(mousePos)) {
                setButtonState(BTN_HOVER);
            }
            else {
                setButtonState(BTN_IDLE);
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        if (buttonState == BTN_ACTIVE) {
            // do nothing
        }
        else {
            Point mousePos = Point(event.mouseMove.x, event.mouseMove.y);
            if (isMouseOn(mousePos)) {
                setButtonState(BTN_HOVER);
            }
            else {
                setButtonState(BTN_IDLE);
            }
        }
    }
    else {
        // do nothing
    }
    return mIsEvent;
}