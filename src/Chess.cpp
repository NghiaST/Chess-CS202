#include "Chess.hpp"

Chess::Chess() {
    pieceBoard = new IngameScreen();
    clock.restart();

    windowSize = Point(1000, 650);
    renderPosition = Point(200, 10);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "ChessLion", sf::Style::Default, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(renderPosition.to2i());
}

Chess::~Chess() {
    delete pieceBoard;
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
        pieceBoard->handleEvent(sfEvent);
    }
    clock.restart();
}

void Chess::update() {
    sf::Time deltaTime = clock.getElapsedTime();
    clock.restart();
    pieceBoard->update(deltaTime);
}

void Chess::render() {
    mWindow.clear(sf::Color::Red);
    pieceBoard->render(mWindow, sf::RenderStates::Default);
    mWindow.display();
}