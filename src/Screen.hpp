#ifndef __Screen_hpp__
#define __Screen_hpp__

#include <SFML/Graphics.hpp>
#include <ctime>
#include "DataControl/Theme.hpp"
#include "DataControl/FileInit.hpp"

enum class ScreenType {
    IngameScreen,
    HomeScreen,
    // MenuScreen,
    // LoadingScreen,
    SettingScreen,
    StatisticsScreen,
    None
};

class Screen {
public:
    Screen();
    virtual ~Screen();
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) = 0;

public:
    bool ifScreenChange() const;
    ScreenType getCurrentScreen() const;
    ScreenType getNextScreen() const;

    void resetScreenChange();

protected:
    sf::Shader shader;
    sf::RenderStates states;
    Theme* theme;

    ScreenType currentScreen;
    ScreenType nextScreen;
    bool isScreenChange;
};

#endif