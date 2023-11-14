#ifndef __TimeButton_hpp__
#define __TimeButton_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Button.hpp"

class TimeButton : sf::Drawable {
public:
    TimeButton(int id, Point renderPositionWhite, Point renderPositionBlack, Point renderSize, const sf::Font* font, const ColorButMulti& colorButMulti);
    ~TimeButton();

    std::string update(sf::Time deltaTime);
    void updateRender();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

    void setReverseTable(bool isReverseTable);
    void setColorBM(const ColorButMulti& colorButMulti);
    void setTime(int time);
    void setTurn(bool isWhiteTurn);
    void setIsCountDown(bool isCountDown);
    void changeTurn();
    void reset();

private:
    Point renderPositionWhite;
    Point renderPositionBlack;

    bool isWhiteTurn;
    bool isCountDown;
    bool isOutOfTime;
    double totalTime;
    double timeWhite;
    double timeBlack;
    bool isReverseTable;

    Button* buttonWhite;
    Button* buttonBlack;
};

#endif