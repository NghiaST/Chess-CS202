#ifndef __HomeScreen_hpp__
#define __HomeScreen_hpp__

#include <SFML/Graphics.hpp>
#include "../Screen.hpp"
#include "../DataControl/Button.hpp"
#include "../DataControl/Image.hpp"

class HomeScreen : public Screen {
public:
    HomeScreen();
    ~HomeScreen();
    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) override;

private:
    Point TitleScreenPosition;

    Point PlayButtonPosition;
    Point PlayButtonSize;

    Point SettingButtonPosition;
    Point SettingButtonSize;

    Point StatisticsButtonPosition;
    Point StatisticsButtonSize;
    

    Point ExitButtonPosition;
    Point ExitButtonSize;

private:
    double mTime;

private:
    Image Background;
    FreeButton* TitleScreen;
    Button* PlayButton;
    Button* SettingButton;
    Button* StatisticsButton;
    Button* ExitButton;
};

#endif
