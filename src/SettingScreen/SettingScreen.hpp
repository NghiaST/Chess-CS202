#ifndef __SettingScreen_hpp__
#define __SettingScreen_hpp__

#include <iostream>
#include "../Screen.hpp"
#include "../DataControl/Image.hpp"

class SettingScreen : public Screen {
public:
    SettingScreen();
    ~SettingScreen();
    void handleEvent(const sf::Event &event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget &target, sf::RenderStates states) override;

private:
    Point boardSize;
    Point boardPosition;

    Point BackButtonSize;
    Point BackButtonPosition;

private:
    Image Background;
    BoardPrint* boardPrint;
    Button* BackButton;
};

#endif