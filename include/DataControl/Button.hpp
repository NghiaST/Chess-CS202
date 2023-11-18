#ifndef __Button_hpp__
#define __Button_hpp__

#include <DataControl/TextBox.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

enum ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_HOLD };

class Button : public TextBox {
public:
    Button(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12, 
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~Button();

    // Mutators
    void setButtonState(ButtonStates buttonState);
    void setColorBM(const ColorButMulti& colorButMulti);

    // Accessors
    int getButtonState() const;
    const ColorButMulti& getColorBM() const { return colorButMulti; }

public:
    // Functions

    /// handleEvent: return 0 if no event, 1 if event
    bool handleEvent(const sf::Event& event);

private:
    ColorButMulti colorButMulti;
    ButtonStates buttonState;
};

#endif