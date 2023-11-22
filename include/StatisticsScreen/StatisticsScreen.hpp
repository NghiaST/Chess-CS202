#ifndef __StatisticsScreen_hpp__
#define __StatisticsScreen_hpp__

#include <Screen.hpp>
#include <IngameScreen/BoardPrint.hpp>
#include <DataControl/Image.hpp>
#include <DataControl/Button.hpp>
#include <StatisticsScreen/Table.hpp>
#include <iostream>

class StatisticsScreen : public Screen {
public:
    StatisticsScreen();
    ~StatisticsScreen();
    void handleEvent(const sf::Event &event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget &target, sf::RenderStates states) override;

    void formatTheme() override;
private:
    Point boardSize;
    Point boardPosition;

    Point BackButtonSize;
    Point BackButtonPosition;

private:
    Image Background;
    BoardPrint* boardPrint;
    Button* BackButton;
    Table* table;
};

#endif