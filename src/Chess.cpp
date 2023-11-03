#include "Chess.hpp"

Chess::Chess() {
    ingameScreen = new IngameScreen();
    clock.restart();

    windowSize = INTERFACE::WINDOWSIZE;
    renderPosition = Point(sf::VideoMode::getDesktopMode().width / 2 - windowSize.x / 2, 10);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "ChessLion", sf::Style::Close, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(renderPosition.to2i());
}

Chess::~Chess() {
    delete ingameScreen;
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
        ingameScreen->handleEvent(sfEvent);
    }
    clock.restart();
}

void Chess::update() {
    sf::Time deltaTime = clock.getElapsedTime();
    clock.restart();
    ingameScreen->update(deltaTime);
}

void Chess::render() {
    mWindow.clear(sf::Color::Red);
    ingameScreen->render(mWindow, sf::RenderStates::Default);
    mWindow.display();
}