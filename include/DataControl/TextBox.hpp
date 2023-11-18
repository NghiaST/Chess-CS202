#ifndef __TextBox_hpp__
#define __TextBox_hpp__

#include <Graphic.hpp>
#include <DataControl/Include.hpp>
#include <DataControl/Color.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

enum BUTTON_ID { Undefined = -1, ButtonHome = 1000, ButtonStart = 2000 };

class TextBox : public Graphic {
public:
    TextBox(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButton& colorButton = Color::ButtonDefault, unsigned int sizeText = 12, 
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~TextBox();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates = sf::RenderStates::Default) const override;

    // Mutators
    void setRenderPosition(Point renderPosition) override;
    void setRenderSize(Point renderSize) override;
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
    Point getRenderOffsetText() const;
    float getThickness() const;
    const ColorButton& getColorButton() const;
    int getButtonID() const;

protected:
    void updateStaticRender();

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

class DynamicTextBox : public TextBox {
public:
    DynamicTextBox(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12, 
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~DynamicTextBox();
    void changeColorState();
    void update(sf::Time deltaTime);
    int getButtonState() const;

private:
    ColorButMulti colorButMulti;
    int colorState;
    double timer;
    
private:
    int velocity;
    int limit;
    double timeMove;
};

#endif