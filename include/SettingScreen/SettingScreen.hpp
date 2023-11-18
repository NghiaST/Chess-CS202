#ifndef __SettingScreen_hpp__
#define __SettingScreen_hpp__

#include <Screen.hpp>
#include <IngameScreen/BoardPrint.hpp>
#include <IngameScreen/PiecePrint.hpp>
#include <DataControl/Image.hpp>
#include <DataControl/Theme.hpp>
#include <DataControl/ButtonOption.hpp>
#include <iostream>

class SettingScreen : public Screen {
public:
    SettingScreen();
    ~SettingScreen();
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
    std::vector<PiecePrint*> piecePrintList;
    Button* BackButton;
    ButtonOption* BackgroundOption;
    ButtonOption* PieceOption;
    ButtonOption* BoardOption;
    ButtonOption* ButOption;
    ButtonOption* TextOption;
};

#endif