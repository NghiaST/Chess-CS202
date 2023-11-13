#include "Screen.hpp"

Screen::Screen() {
    shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment);
    states.shader = &shader;
    theme = new Theme();
    theme->setTheme(FileInit::LoadTheme());
    // theme->loadFile();
    srand(time(NULL));
    isScreenChange = false;
    nextScreen = ScreenType::None;
}

Screen::~Screen() {
    delete theme;
}

bool Screen::ifScreenChange() const {
    return isScreenChange;
}

ScreenType Screen::getCurrentScreen() const {
    return currentScreen;
}

ScreenType Screen::getNextScreen() const {
    return nextScreen;
}

void Screen::resetScreenChange() {
    isScreenChange = false;
    nextScreen = ScreenType::None;
}
