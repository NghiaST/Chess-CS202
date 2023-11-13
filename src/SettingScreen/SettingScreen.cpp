#include "SettingScreen.hpp"

SettingScreen::SettingScreen() : Screen() {
    currentScreen = ScreenType::SettingScreen;

    boardSize = Point(64, 64) * 8;
    boardPosition = Point(150, 70);
    
    BackButtonSize = Point(130, 60);
    BackButtonPosition = Point(900, 500);

    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    BackButton = new Button(4, BackButtonPosition, BackButtonSize, true, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");
}

SettingScreen::~SettingScreen() {
    delete BackButton;
}

void SettingScreen::handleEvent(const sf::Event& event) {
    if (BackButton->handleEvent(event)) {
        isScreenChange = true;
        nextScreen = ScreenType::HomeScreen;
    }
}

void SettingScreen::update(sf::Time deltaTime) {
}

void SettingScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    BackButton->updateRender();
    
    Background.draw(target);
    target.draw(*BackButton);
}