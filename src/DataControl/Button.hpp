#ifndef __Button_hpp__
#define __Button_hpp__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "StaticButton.hpp"

enum ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_HOLD };

class Button : public StaticButton {
public:
    Button(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12, 
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~Button();

    // Mutators
    void setButtonState(ButtonStates buttonState);

    // Accessors
    int getButtonState() const;

public:
    // Functions

    /// handleEvent: return 0 if no event, 1 if event
    bool handleEvent(const sf::Event& event);
    virtual void updateRender();
    
private:
    ColorButMulti colorButMulti;
    ButtonStates buttonState;
};

class FreeButton : public StaticButton {
public:
    FreeButton(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12, 
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~FreeButton();
    void changeButtonState();
    void update(sf::Time deltaTime);
    int getButtonState() const;

private:
    ColorButMulti colorButMulti;
    int buttonState;
    double timer;
    
private:
    int velocity;
    int limit;
    double timeMove;
};

#endif