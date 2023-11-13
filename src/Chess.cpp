#include "Chess.hpp"

Chess::Chess() {
    ingameScreen = new IngameScreen();
    homeScreen = new HomeScreen();
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
    // exit(0);
    delete homeScreen;
    // delete ingameScreen;
    // delete mScreen;
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
        }
        mScreen->handleEvent(sfEvent);
    }
}

void Chess::update() {
    sf::Time deltaTime = clock.getElapsedTime();
    clock.restart();
    if (mScreen->ifScreenChange()) {
        changeScreen(mScreen->getNextScreen());
    }
    mScreen->update(deltaTime);
}

void Chess::render() {
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
        case ScreenType::None:
            mWindow.close();
            break;
        default:
            printf("Bug at Chess::changeScreen\n");
            exit(1);
    }
    mScreen->resetScreenChange();
}