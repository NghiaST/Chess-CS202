#ifndef __CustomScreen_hpp__
#define __CustomScreen_hpp__

#include <Screen.hpp>
#include <IngameScreen/BoardPrint.hpp>
#include <IngameScreen/PiecePrint.hpp>
#include <DataControl/Image.hpp>
#include <DataControl/Theme.hpp>
#include <DataControl/ButtonOption.hpp>
#include <CustomScreen/BoardCustomManager.hpp>
#include <iostream>

class CustomScreen : public Screen {
public:
    CustomScreen();
    ~CustomScreen();
    void handleEvent(const sf::Event &event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget &target, sf::RenderStates states) override;

    void formatTheme() override;

private:
    Point boardSize;
    Point boardPosition;

    Point buttonSize;
    Point actionButtonSize;
    Point ResetButtonPosition;
    Point ClearButtonPosition;
    Point PlayButtonPosition;
    Point SaveAndBackButtonPosition;
    Point BackButtonPosition;

private:
    Image Background;
    BoardCustomManager* boardCustomManager;
    Button* ResetButton;
    Button* ClearButton;
    Button* PlayButton;
    Button* SaveAndBackButton;
    Button* BackButton;
};

#endif