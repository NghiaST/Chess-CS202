#include "Button.hpp"

Button::Button(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
        const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText, 
        std::string text, float thickness, Point renderOffsetText)
    : StaticButton(buttonID, renderPosition, renderSize, isPositionCenter, isRenderTextOrigin, 
            sfFont, Color::ColorButtonDefault, sizeText, text, thickness, renderOffsetText)
{
    this->colorButMulti = colorButMulti;
    this->buttonState = BTN_IDLE;
    updateRender();
}

Button::~Button() {
}

// Mutators
void Button::setButtonState(ButtonStates buttonState) {
    this->buttonState = buttonState;
    setColorButton(colorButMulti.get(buttonState));
}

// Accessors
int Button::getButtonState() const {
    return this->buttonState;
}

//Functions
bool Button::handleEvent(const sf::Event& event) {
    /* Update the booleans for hover and pressed */
    bool isEvent = false;
    if (event.type == sf::Event::MouseButtonPressed) {
        Point mousePos = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOn(mousePos)) {
                setButtonState(BTN_ACTIVE);
                isEvent = true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        Point mousePos = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
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
    else if (event.type == sf::Event::MouseLeft) {
        setButtonState(BTN_IDLE);
    }
    else if (event.type == sf::Event::MouseEntered) {
        Point mousePos = Point(event.mouseMove.x, event.mouseMove.y);
        if (isMouseOn(mousePos)) {
            setButtonState(BTN_HOVER);
        }
        else {
            setButtonState(BTN_IDLE);
        }
    }
    else {
        // do nothing
    }
    updateRender();
    return isEvent;
}

void Button::updateRender() {
    setColorButton(colorButMulti.get(buttonState));
    updateStaticRender();
}

FreeButton::FreeButton(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, const sf::Font *sfFont, const ColorButMulti &colorButMulti, unsigned int sizeText, std::string text, float thickness, Point renderOffsetText) 
    : StaticButton(buttonID, renderPosition, renderSize, isPositionCenter, isRenderTextOrigin, sfFont, Color::ColorButtonDefault, sizeText, text, thickness, renderOffsetText)
{
    this->colorButMulti = colorButMulti;
    this->buttonState = BTN_IDLE;
    changeButtonState();
    timer = 0;
}

FreeButton::~FreeButton() {
}

void FreeButton::changeButtonState() {
    buttonState = (buttonState + 1) % 10;
    setColorButton(colorButMulti.get(buttonState));
    updateStaticRender();
}

void FreeButton::update(sf::Time deltaTime) {
    timer += deltaTime.asSeconds();
    if (timer > 1) {
        timer -= 1;
        changeButtonState();
    }
}

int FreeButton::getButtonState() const {
    return buttonState;
}
