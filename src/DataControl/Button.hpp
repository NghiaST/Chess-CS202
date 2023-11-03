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
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override {}
    
private:
    ColorButMulti colorButMulti;
    ButtonStates buttonState;
};

#endif