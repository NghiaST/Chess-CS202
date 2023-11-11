#ifndef __TimeButton_hpp__
#define __TimeButton_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Button.hpp"

class TimeButton {
public:
    TimeButton(int id, Point renderPositionWhite, Point renderPositionBlack, Point renderSize, const sf::Font* font, const ColorButMulti& colorButMulti);
    ~TimeButton();

    std::string update(sf::Time deltaTime);
    void updateRender();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const;

    void setTime(int time);
    void setTurn(bool isWhiteTurn);
    void setIsCountDown(bool isCountDown);
    void changeTurn();
    void reset();

private:
    bool isWhiteTurn;
    bool isCountDown;
    bool isOutOfTime;
    double totalTime;
    double timeWhite;
    double timeBlack;

    Button* buttonWhite;
    Button* buttonBlack;
};

#endif