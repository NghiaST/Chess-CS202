#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <DataControl/Include.hpp>
#include <DataControl/Theme.hpp>
#include <HomeScreen/HomeScreen.hpp>
#include <IngameScreen/IngameScreen.hpp>
#include <PuzzlesScreen/PuzzlesScreen.hpp>
#include <SettingScreen/SettingScreen.hpp>
#include <StatisticsScreen/StatisticsScreen.hpp>
#include <OptionScreen/OptionScreen.hpp>
#include <SFML/Graphics.hpp>

class Chess {
public:
    Chess();
    ~Chess();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    void changeScreen(ScreenType screenType);

private:
    sf::RenderWindow mWindow;
    Screen* mScreen;
    IngameScreen* ingameScreen;
    HomeScreen* homeScreen;
    PuzzlesScreen* puzzlesScreen;
    SettingScreen* settingScreen;
    StatisticsScreen* statisticsScreen;
    OptionScreen* optionScreen;

    Point windowSize;
    Point windowPosition;
    sf::Clock clock;
};

#endif