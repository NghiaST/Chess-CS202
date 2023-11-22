#include <StatisticsScreen/StatisticsScreen.hpp>
#include <StatisticsScreen/ProcessStatistics.hpp>

StatisticsScreen::StatisticsScreen() : Screen() {
    currentScreen = ScreenType::StatisticsScreen;

    boardSize = Point(64, 64) * 8;
    boardPosition = Point(150, 70);
    
    BackButtonSize = Point(130, 60);
    BackButtonPosition = Point(900, 500);

    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    BackButton = new Button(4, BackButtonPosition, BackButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");

    table = new Table(0, Point(150, 50), Point(130, 60), &theme->getFont(), theme->getColorDefault(), 16, Statistics().getStatistics());
}

StatisticsScreen::~StatisticsScreen() {
    delete BackButton;
    delete table;
}

void StatisticsScreen::handleEvent(const sf::Event& event) {
    if (BackButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::HomeScreen;
    }
    table->handleEvent(event);
}

void StatisticsScreen::update(sf::Time deltaTime) {
}

void StatisticsScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    Background.draw(target);
    target.draw(*BackButton);
    target.draw(*table);
}

void StatisticsScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    BackButton->setColorBM(theme->getColorDefault());
}