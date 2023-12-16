#include <OptionScreen/OptionScreen.hpp>
#include <DataControl/GameAttributes.hpp>

OptionScreen::OptionScreen() : Screen() {
    currentScreen = ScreenType::OptionScreen;
    
    int middle = INTERFACE::WindowSize.x / 2;

    ButtonSize = Point(130, 60);
    ButtonOptionSize = Point(300, 70);

    VariantsOptionPosition   = Point(middle, 80 * 1);
    ModeOptionPosition       = Point(middle, 80 * 2);
    DifficultyOptionPosition = Point(middle, 80 * 3);
    TimeTotalOptionPosition  = Point(middle, 80 * 4);
    TimeExtraOptionPosition  = Point(middle, 80 * 5);
    BotHelpOptionPosition    = Point(middle, 80 * 6);

    CustomButtonPosition   = Point(middle - 1.8 * ButtonSize.x, 600);
    ContinueButtonPosition = Point(middle - 0.6 * ButtonSize.x, 600);
    NewGameButtonPosition  = Point(middle + 0.6 * ButtonSize.x, 600);
    BackButtonPosition     = Point(middle + 1.8 * ButtonSize.x, 600);

    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);

    CustomButton   = new Button(0, CustomButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Custom");
    ContinueButton = new Button(1, ContinueButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Continue");
    NewGameButton  = new Button(2, NewGameButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "New Game");
    BackButton     = new Button(3, BackButtonPosition, ButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");

    GameAttributes gameAttributes = GameAttributes();

    std::vector<std::string> variantsList = {"Standard", "King of the Hill", "Atomic"};
    std::vector<std::string> modeList = {"PvE White", "PvE Black", "PvP", "EvE"};
    std::vector<std::string> levelList = {"Easy", "Medium", "Hard"};
    std::vector<std::string> timeTotalList = {"1m", "2m", "3m", "5m", "10m", "15m", "30m", "60m"};
    std::vector<std::string> timeExtraList = {"0s", "2s", "5s", "10s", "15s", "30s"};
    std::vector<std::string> botHelpList = {"Bot Help Off", "Bot Help On"};

    VariantsOption   = new ButtonOption(3, VariantsOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, variantsList, gameAttributes.getVariants(), 2);
    ModeOption       = new ButtonOption(4, ModeOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, modeList, gameAttributes.getMode(), 2);
    DifficultyOption = new ButtonOption(5, DifficultyOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, levelList, gameAttributes.getLevel(), 2);
    TimeTotalOption  = new ButtonOption(6, TimeTotalOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, timeTotalList, gameAttributes.getTimeTotalMode(), 2);
    TimeExtraOption  = new ButtonOption(7, TimeExtraOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, timeExtraList, gameAttributes.getTimeExtraMode(), 2);
    BotHelpOption    = new ButtonOption(8, BotHelpOptionPosition, ButtonOptionSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, botHelpList, gameAttributes.getIsBotHelp(), 2);
}

OptionScreen::~OptionScreen() {
    delete CustomButton;
    delete ContinueButton;
    delete NewGameButton;
    delete BackButton;
    delete VariantsOption;
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
    if (VariantsOption->handleEvent(event)) {
        isChange = true;
    }
    if (ModeOption->handleEvent(event)) {
        isChange = true;
    }
    if (DifficultyOption->handleEvent(event)) {
        isChange = true;
    }
    if (TimeTotalOption->handleEvent(event)) {
        isChange = true;
    }
    if (TimeExtraOption->handleEvent(event)) {
        isChange = true;
    }
    if (BotHelpOption->handleEvent(event)) {
        isChange = true;
    }
    if (isChange) {
        GameAttributes gameAttributes(VariantsOption->getCurrentSelection(), ModeOption->getCurrentSelection(), DifficultyOption->getCurrentSelection(), TimeTotalOption->getCurrentSelection(), TimeExtraOption->getCurrentSelection(), (bool) BotHelpOption->getCurrentSelection());
        FileManager::SaveThemeConfig(theme->getThemeIndex(), gameAttributes);
    }
    if (CustomButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::CustomScreen;
    }
    if (ContinueButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::IngameScreen;
    }
    if (NewGameButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::IngameScreen;
        FileManager::RemoveSaveGame();
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
    target.draw(*CustomButton);
    target.draw(*ContinueButton);
    target.draw(*NewGameButton);
    target.draw(*BackButton);
    target.draw(*VariantsOption);
    target.draw(*ModeOption);
    target.draw(*DifficultyOption);
    target.draw(*TimeTotalOption);
    target.draw(*TimeExtraOption);
    target.draw(*BotHelpOption);
}

void OptionScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    CustomButton->setColorBM(theme->getColorDefault());
    ContinueButton->setColorBM(theme->getColorDefault());
    NewGameButton->setColorBM(theme->getColorDefault());
    BackButton->setColorBM(theme->getColorDefault());
    ModeOption->setColorBM(theme->getColorDefault());
    DifficultyOption->setColorBM(theme->getColorDefault());
    TimeTotalOption->setColorBM(theme->getColorDefault());
    TimeExtraOption->setColorBM(theme->getColorDefault());
    BotHelpOption->setColorBM(theme->getColorDefault());
}
