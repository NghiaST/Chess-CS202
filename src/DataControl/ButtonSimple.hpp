// #ifndef __Button_hpp__
// #define __Button_hpp__

// #include <iostream>
// #include <ctime>
// #include <cstdlib>
// #include <sstream>

// #include <SFML/Graphics.hpp>
// // #include <SFML/Window.hpp>
// // #include <SFML/System.hpp>
// // #include <SFML/Audio.hpp>
// #include "../Graphic.hpp"
// #include "Color.hpp"

// enum ButtonStates { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_HOLD };
// enum ButtonName { ButtonHome = 0, ButtonStart };

// class Button : public Graphic, public sf::Drawable {
// public:
//     Button(ButtonName buttonName, sf::Vector2f renderPosition, sf::Vector2f renderSize, const sf::Font* sfFont, 
//             const ColorButMulti& colorButMulti, int charactersize = 12, std::string text = "");
//     ~Button();

//     //Accessors
//     int getButtonState() const;
//     const bool isPressed() const;

//     //Functions
//     virtual void handleClick(const sf::Vector2f mousePos);
//     virtual void update();
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates = sf::RenderStates::Default) const;

// private:
//     ButtonStates buttonState;
//     ButtonName buttonName;

//     sf::RectangleShape shape;
//     sf::Font* sfFont;
//     sf::Text sfText;
    
//     const ColorButMulti* colorButMulti;

//     /// customize button
//     int characterSize;
//     int sizeText;
//     std::string text;
//     float thickness;
// };

// #endif

// #include "Button.hpp"

// Button::Button(Point renderPosition, Point renderSize, const sf::Font* sfFont, 
//             const sf::Color renderColor, unsigned int characterSize = 12, std::string text = "")
// {
//     this->renderPosition = renderPosition;
//     this->renderSize = renderSize;
//     this->sfFont = sfFont;
//     this->renderColor = renderColor;

//     this->buttonState = BTN_IDLE;
//     this->buttonName = buttonName;
//     this->characterSize = characterSize;
//     this->text = text;

//     this->shape.setPosition(sf::Vector2f(x, y));
//     this->shape.setSize(sf::Vector2f(width, height));

//     this->font = font;
//     this->text.setFont(*this->font);
//     this->text.setString(text);
//     this->text.setFillColor(sf::Color::White);
//     this->text.setCharacterSize(characterSize);
//     this->text.setPosition(
//         this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
//         this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
//     );

//     this->shape.setFillColor(this->idleColor);
// }

// Button::~Button() {
// }

// void Button::update(const sf::Vector2f mousePos) {
//     /* Update the booleans for hover and pressed */

//     // Idle
//     this->buttonState = BTN_IDLE;

//     // Hover
//     if (this->shape.getGlobalBounds().contains(mousePos)) {
//         this->buttonState = BTN_HOVER;

//         // Pressed
//         if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//             this->buttonState = BTN_ACTIVE;
//         }
//     }

//     switch (this->buttonState) {
//     case BTN_IDLE:
//         this->shape.setFillColor(this->idleColor);
//         break;
//     case BTN_HOVER:
//         this->shape.setFillColor(this->hoverColor);
//         break;
//     case BTN_ACTIVE:
//         this->shape.setFillColor(this->activeColor);
//         break;
//     default:
//         this->shape.setFillColor(sf::Color::Red);
//         break;
//     }
// }

// //Functions
// void Button::render(sf::RenderTarget* target) {
//     target->draw(this->shape);
//     target->draw(this->text);
//     sf::Event
// }