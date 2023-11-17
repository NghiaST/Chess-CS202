#ifndef __OptionScreen_hpp__
#define __OptionScreen_hpp__

#include "../Screen.hpp"
#include "../DataControl/Image.hpp"
#include "../IngameScreen/BoardPrint.hpp"
#include "../IngameScreen/PiecePrint.hpp"
#include "../DataControl/ButtonOption.hpp"
#include "../DataControl/Theme.hpp"
#include <iostream>

class OptionScreen : public Screen {
public:
    OptionScreen();
    ~OptionScreen();
    void handleEvent(const sf::Event &event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget &target, sf::RenderStates states) override;

    void formatTheme() override;

private:
    Point ButtonSize;
    Point ButtonOptionSize;

    Point ContinueButtonPosition;
    Point NewGameButtonPosition;
    Point BackButtonPosition;

    Point ModeOptionPosition;
    Point DifficultyOptionPosition;
    Point BotHelpOptionPosition;

private:
    Image Background;
    Button* ContinueButton;
    Button* NewGameButton;
    Button* BackButton;
    ButtonOption* ModeOption;
    ButtonOption* DifficultyOption;
    ButtonOption* BotHelpOption;
};

#endif