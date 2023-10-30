#include "Event.hpp"

Event::Event() {
    timeMouseHold = 0;
    timeKeyHold = 0;
    isMouseMoved = false;
    keyboardStatus = 0;
    mouseStatus = 0;
    keyboardKey = 0;
    mousePos = Point(0, 0);
    isChangeStatesWindow = false;
    isCloseWindow = false;
    clock.restart();
}

Event::~Event() {}

void Event::setMouseStatus(int mouseStatus) {
    this->mouseStatus = mouseStatus;
}

void Event::setMousePos(Point mousePos) {
    this->mousePos = mousePos;
}

void Event::setKeyboardStatus(int keyboardStatus) {
    this->keyboardStatus = keyboardStatus;
}

void Event::setKeyboardKey(int keyboardKey) {
    this->keyboardKey = keyboardKey;
}

bool Event::IsKeyPressed() const {
    return keyboardStatus == 1;
}

bool Event::IsKeyHold() const {
    return keyboardStatus == 2;
}

bool Event::IsKeyReleased() const {
    return keyboardStatus == 3;
}

bool Event::IsMousePressed() const {
    return mouseStatus == 1;
}

bool Event::IsMouseHold() const {
    return mouseStatus == 2;
}

bool Event::IsMouseReleased() const {
    return mouseStatus == 3;
}

bool Event::IsMouseScrolled() const {
    return mouseStatus == 4;
}

bool Event::IsMouseMoved() const {
    return isMouseMoved;
}

bool Event::IsChangeStatesWindow() const {
    return isChangeStatesWindow;
}

bool Event::IsCloseWindow() const {
    return isCloseWindow;
}

int Event::getKeyboardStatus() const {
    return keyboardStatus;
}

int Event::getMouseStatus() const {
    return mouseStatus;
}

int Event::getKeyboardKey() const {
    return keyboardKey;
}

Point Event::getMousePos() const {
    return mousePos;
}

void Event::processEvents(const sf::Event& sfEvent)
{
    isChange = false;
    timeEvent = clock.getElapsedTime().asSeconds();
    clock.restart();

    /// update mouse position
    if (sfEvent.type == sf::Event::MouseMoved) {
        mousePos = Point(sfEvent.mouseMove.x, sfEvent.mouseMove.y);
        isMouseMoved = true;
    }

    /// update mouse status
    if (sfEvent.type == sf::Event::MouseButtonPressed) {
        mouseStatus = EventType::PRESSED;
        timeMouseHold = 0;
        isChange = true;
    }
    else if (sfEvent.type == sf::Event::MouseButtonReleased) {
        mouseStatus = EventType::RELEASED;
        timeMouseHold = 0;
        isChange = true;
    }
    else {
        if (mouseStatus == EventType::PRESSED) {
            mouseStatus = EventType::HOLD;
            isChange = true;
        }
        else if (mouseStatus != EventType::NONE) {
            mouseStatus = EventType::NONE;
            isChange = true;
        }
    }

    if (sfEvent.type == sf::Event::KeyPressed) {
        keyboardStatus = EventType::PRESSED;
    }
    if (sfEvent.type == sf::Event::KeyReleased) {
        keyboardStatus = EventType::RELEASED;
    }
    if (sfEvent.type == sf::Event::TextEntered) {
        keyboardStatus = EventType::PRESSED;
        keyboardName = sfEvent.text.unicode;
    }
}

void Event::refreshEvent() {
    isChange = false;
    timeEvent = clock.getElapsedTime().asSeconds();
    clock.restart();
    if (mouseStatus == EventType::HOLD) {
        timeMouseHold += timeEvent;
    }
    if (mouseStatus == EventType::PRESSED) {
        mouseStatus = EventType::HOLD;
        timeMouseHold += timeEvent;
        isChange = true;
    }
    else if (mouseStatus != EventType::NONE) {
        mouseStatus = EventType::NONE;
        isChange = true;
    }
}