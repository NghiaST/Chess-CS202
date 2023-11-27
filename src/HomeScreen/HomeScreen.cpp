#include <HomeScreen/HomeScreen.hpp>

HomeScreen::HomeScreen() : Screen() {
    currentScreen = ScreenType::HomeScreen;
    mTime = 0;

    int middle = INTERFACE::WindowSize.x / 2;

    TitleScreenPosition  = Point(middle, 150);

    PlayButtonSize       = Point(130, 60);
    PlayButtonPosition       = Point(middle, 300);

    PuzzlesButtonSize    = Point(130, 60);
    PuzzlesButtonPosition    = Point(middle, 300 + 1 * 1.2 * PuzzlesButtonSize.y);
    
    SettingButtonSize    = Point(130, 60);
    SettingButtonPosition    = Point(middle, 300 + 2 * 1.2 * PlayButtonSize.y);

    StatisticsButtonSize = Point(130, 60);
    StatisticsButtonPosition = Point(middle, 300 + 3 * 1.2 * PlayButtonSize.y);

    ExitButtonSize       = Point(130, 60);
    ExitButtonPosition       = Point(middle, 300 + 4 * 1.2 * PlayButtonSize.y);


    Background = Image(theme->getTitleScreenTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    TitleScreen = new DynamicTextBox(0, TitleScreenPosition, Point(0, 0), true, true, &theme->getFontTitle(), theme->getColorTitle(), 100, "LION CHESS");
    PlayButton = new Button(1, PlayButtonPosition, PlayButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Play");
    PuzzlesButton = new Button(2, PuzzlesButtonPosition, PuzzlesButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Puzzles");
    SettingButton = new Button(3, SettingButtonPosition, SettingButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Setting");
    StatisticsButton = new Button(4, StatisticsButtonPosition, StatisticsButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Statistics");
    ExitButton = new Button(5, ExitButtonPosition, ExitButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Exit");
}

HomeScreen::~HomeScreen() {
    delete TitleScreen;
    delete PlayButton;
    delete SettingButton;
    delete StatisticsButton;
    delete ExitButton;
}

void HomeScreen::handleEvent(const sf::Event& event) {
    if (PlayButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::OptionScreen;
    }
    if (PuzzlesButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::PuzzlesScreen;
    }
    if (SettingButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::SettingScreen;
    }
    if (StatisticsButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::StatisticsScreen;
    }
    if (ExitButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::None;
    }
}

void HomeScreen::update(sf::Time deltaTime) {
    TitleScreen->update(deltaTime);
}
void HomeScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    Background.draw(target);
    target.draw(*TitleScreen);
    target.draw(*PlayButton);
    target.draw(*PuzzlesButton);
    target.draw(*SettingButton);
    target.draw(*StatisticsButton);
    target.draw(*ExitButton);
}

void HomeScreen::formatTheme() {
    PlayButton->setColorBM(theme->getColorDefault());
    SettingButton->setColorBM(theme->getColorDefault());
    StatisticsButton->setColorBM(theme->getColorDefault());
    ExitButton->setColorBM(theme->getColorDefault());
}