#include "Chess.hpp"

Chess::Chess() {
    homeScreen = new HomeScreen();
    settingScreen = new SettingScreen();
    ingameScreen = new IngameScreen();
    statisticsScreen = new StatisticsScreen();
    mScreen = homeScreen;
    clock.restart();

    windowSize = INTERFACE::WindowSize;
    renderPosition = Point(sf::VideoMode::getDesktopMode().width / 2 - windowSize.x / 2, 10);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "ChessLion", sf::Style::Close, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(renderPosition.to2i());
}

Chess::~Chess() {
    delete homeScreen;
    delete settingScreen;
    delete ingameScreen;
    delete statisticsScreen;
}

void Chess::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Chess::processEvents() {
    sf::Event sfEvent;
    while (mWindow.pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            mWindow.close();
            return;
        }
        mScreen->handleEvent(sfEvent);
    }
}

void Chess::update() {
    if (!mWindow.isOpen()) {
        return;
    }
    sf::Time deltaTime = clock.getElapsedTime();
    clock.restart();
    if (mScreen->ifScreenChange()) {
        changeScreen(mScreen->getNextScreen());
    }
    mScreen->update(deltaTime);
}

void Chess::render() {
    if (!mWindow.isOpen()) {
        return;
    }
    mWindow.clear(sf::Color::Red);
    mScreen->render(mWindow, sf::RenderStates::Default);
    mWindow.display();
}

void Chess::changeScreen(ScreenType screenType) {
    switch (screenType) {
        case ScreenType::IngameScreen:
            mScreen = ingameScreen;
            break;
        case ScreenType::HomeScreen:
            mScreen = homeScreen;
            break;
        case ScreenType::SettingScreen:
            mScreen = settingScreen;
            break;
        case ScreenType::StatisticsScreen:
            mScreen = statisticsScreen;
            break;
        case ScreenType::None:
            mWindow.close();
            break;
        default:
            printf("Bug at Chess::changeScreen\n");
            exit(1);
    }
    mScreen->resetScreenChange();
    mScreen->formatTheme();
}