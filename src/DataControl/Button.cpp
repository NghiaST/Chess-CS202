#include "Button.hpp"

Button::Button(int buttonID, Point renderPosition, Point renderSize, const sf::Font* sfFont, 
            const ColorButMulti& colorButMulti, unsigned int sizeText, std::string text)
    : StaticButton(buttonID, renderPosition, renderSize, sfFont, 
                Color::ColorButtonDefault, sizeText, text, -1, true, Point(0, 0))
{
    this->colorButMulti = colorButMulti;
    this->buttonState = BTN_IDLE;
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
bool Button::handleEvent(sf::Event& event) {
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
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        Point mousePos = Point(event.mouseMove.x, event.mouseMove.y);
        if (isMouseOn(mousePos)) {
            setButtonState(BTN_HOVER);
        }
        else {
            setButtonState(BTN_IDLE);
        }
    }
    else if (event.type == sf::Event::MouseLeft) {
        this->buttonState = BTN_IDLE;
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
    return isEvent;
}

void Button::update() {
    setColorButton(colorButMulti.get(buttonState));
}