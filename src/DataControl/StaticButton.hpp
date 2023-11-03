#ifndef __StaticButton_hpp__
#define __StaticButton_hpp__

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "../Graphic.hpp"
#include "Include.hpp"
#include "Color.hpp"

enum BUTTON_ID { Undefined = -1, ButtonHome = 1000, ButtonStart = 2000 };

class StaticButton : public Graphic, public sf::Drawable {
public:
    typedef std::unique_ptr<StaticButton> Ptr;

public:
    StaticButton(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButton& colorButton = Color::ColorButtonDefault, unsigned int sizeText = 12, 
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~StaticButton();

    // Mutators
    void setFont(const sf::Font* sfFont);
    void setSizeText(unsigned int sizeText);
    void setText(std::string text);
    void setRenderOffsetText(Point renderOffsetText);
    void setIsRenderTextOrigin(bool isRenderTextOrigin);
    void setThickness(float thickness);
    void setColorButton(const ColorButton& colorButton);
    void setButtonID(int buttonID);

    // Accessors
    const sf::Font* getFont() const;
    int getSizeText() const;
    std::string getText() const;
    float getThickness() const;
    const ColorButton& getColorButton() const;
    int getButtonID() const;

public:
    // Functions
    void updateStaticRender();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates = sf::RenderStates::Default) const;
    virtual void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

private:
    sf::RectangleShape shape;
    const sf::Font* sfFont;
    sf::Text sfText;
    
    /// Name of Button
    int buttonID;

    /// customize button
    ColorButton colorButton;
    Point renderOffsetText;
    bool isRenderTextOrigin;
    unsigned int sizeText;
    std::string text;
    float thickness;
};

#endif