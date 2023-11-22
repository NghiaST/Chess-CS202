#include <OptionScreen/OptionScreen.hpp>

OptionScreen::OptionScreen() : Screen() {
    currentScreen = ScreenType::OptionScreen;
    
    int middle = INTERFACE::WindowSize.x / 2;

    ButtonSize = Point(130, 60);
    ButtonOptionSize = Point(300, 80);

    ModeOptionPosition       = Point(middle, 90);
    DifficultyOptionPosition = Point(middle, 180);
    BotHelpOptionPosition    = Point(middle, 270);
    TimeTotalOptionPosition  = Point(middle, 360);
    TimeExtraOptionPosition  = Point(middle, 450);

    ContinueButtonPosition = Point(middle - 1.2 * ButtonSize.x, 600);
    NewGameButtonPosition  = Point(middle - 0.0 * ButtonSize.x, 600);
    BackButtonPosition     = Point(middle + 1.2 * ButtonSize.x, 600);

    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);

    ContinueButton = new Button(1, ContinueButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Continue");
    NewGameButton  = new Button(2, NewGameButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "New Game");
    BackButton     = new Button(3, BackButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");

    int mode, level;
    bool isBotHelp;
    int timeTotal, timeExtra;
    FileInit::LoadOptions(mode, level, isBotHelp, timeTotal, timeExtra);

    std::vector<std::string> modeList = {"PvE White", "PvE Black", "PvP", "EvE"};
    std::vector<std::string> levelList = {"Easy", "Medium", "Hard"};
    std::vector<std::string> botHelpList = {"Bot Help Off", "Bot Help On"};
    std::vector<std::string> timeTotalList = {"1m", "2m", "3m", "5m", "10m", "15m", "30m", "60m"};
    std::vector<std::string> timeExtraList = {"0s", "2s", "5s", "10s", "15s", "30s"};

    ModeOption       = new ButtonOption(4, ModeOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, modeList, mode, 2);
    DifficultyOption = new ButtonOption(5, DifficultyOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, levelList, level, 2);
    BotHelpOption    = new ButtonOption(6, BotHelpOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, botHelpList, isBotHelp, 2);
    TimeTotalOption  = new ButtonOption(7, TimeTotalOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, timeTotalList, timeTotal, 2);
    TimeExtraOption  = new ButtonOption(8, TimeExtraOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, timeExtraList, timeExtra, 2);
}

OptionScreen::~OptionScreen() {
    delete ContinueButton;
    delete NewGameButton;
    delete BackButton;
    delete ModeOption;
    delete DifficultyOption;
    delete BotHelpOption;
    delete TimeTotalOption;
    delete TimeExtraOption;
}

void OptionScreen::handleEvent(const sf::Event& event) {
    if (BackButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::HomeScreen;
    }

    bool isChange = false;
    if (ModeOption->handleEvent(event)) {
        isChange = true;
    }
    if (DifficultyOption->handleEvent(event)) {
        isChange = true;
    }
    if (BotHelpOption->handleEvent(event)) {
        isChange = true;
    }
    if (TimeTotalOption->handleEvent(event)) {
        isChange = true;
    }
    if (TimeExtraOption->handleEvent(event)) {
        isChange = true;
    }
    if (isChange) {
        FileInit::SaveConfig(theme->getThemeIndex(), ModeOption->getCurrentSelection(), DifficultyOption->getCurrentSelection(), (bool) BotHelpOption->getCurrentSelection(), TimeTotalOption->getCurrentSelection(), TimeExtraOption->getCurrentSelection());
    }
    if (ContinueButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::IngameScreen;
    }
    if (NewGameButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::IngameScreen;
        FileInit::RemoveSaveGame();
    }
    if (BackButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::HomeScreen;
    }
}

void OptionScreen::update(sf::Time deltaTime) {
}

void OptionScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    Background.draw(target);
    target.draw(*ContinueButton);
    target.draw(*NewGameButton);
    target.draw(*BackButton);
    target.draw(*ModeOption);
    target.draw(*DifficultyOption);
    target.draw(*BotHelpOption);
    target.draw(*TimeTotalOption);
    target.draw(*TimeExtraOption);
}

void OptionScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    ContinueButton->setColorBM(theme->getColorDefault());
    NewGameButton->setColorBM(theme->getColorDefault());
    BackButton->setColorBM(theme->getColorDefault());
    ModeOption->setColorBM(theme->getColorDefault());
    DifficultyOption->setColorBM(theme->getColorDefault());
    BotHelpOption->setColorBM(theme->getColorDefault());
    TimeTotalOption->setColorBM(theme->getColorDefault());
    TimeExtraOption->setColorBM(theme->getColorDefault());
}
