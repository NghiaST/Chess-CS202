#ifndef __Event_hpp__
#define __Event_hpp__

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Theme.hpp"

class Chess;

class Event {   /// may be update: add left/right mouse
private:
    sf::Event sfEvent;
    sf::Clock clock;
    double timeEvent;
    bool isChange;

    Point mousePos;

    double timeMouseHold;
    double timeKeyHold;

    int mouseStatus; // 0: none, 1: clicked, 2: pressed, 3: released, 4: scrolled
    int keyboardStatus; // 0: none, 1: pressed, 2: hold, 3: released

    int mouseCode;
    int keyboardCode;

    bool isChangeStatesWindow;    // check if when click, it change status of the screen, for particularly cases, such as hold key then change states
    bool isCloseWindow;

public:
    enum EventType {
        NONE = 0,
        PRESSED = 1,
        HOLD = 2,
        RELEASED = 3,
        SCROLLED = 4
    };

public:
    Event();
    ~Event();

    void setMouseStatus(int mouseStatus);
    void setMousePos(Point mousePos);
    void setKeyboardStatus(int keyboardStatus);
    void setKeyboardKey(int keyboardKey);

public:
    bool IsKeyPressed() const;
    bool IsKeyHold() const;
    bool IsKeyReleased() const;
    bool IsMousePressed() const;
    bool IsMouseHold() const;
    bool IsMouseReleased() const;
    bool IsMouseScrolled() const;
    bool IsMouseMoved() const;
    bool IsChangeStatesWindow() const;
    bool IsCloseWindow() const;

    int getKeyboardStatus() const;
    int getMouseStatus() const;
    int getKeyboardKey() const;
    Point getMousePos() const;

    void processEvents(const sf::Event& sfEvent);
    void refreshEvent();
};

#endif