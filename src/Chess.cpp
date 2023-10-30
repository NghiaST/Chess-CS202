#include "Chess.hpp"

Chess::Chess() {
    pieceBoard = new PieceBoard();
    clock.restart();

    windowSize = Point(1000, 650);
    renderPosition = sf::Vector2i(200, 10);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "ChessLion", sf::Style::Default, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(renderPosition);
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
    Point mousePos = sf::Mouse::getPosition(mWindow);
    pieceBoard->handleEvent(sfEvent, mousePos, clock.getElapsedTime().asSeconds());
    clock.restart();
    while (mWindow.pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            mWindow.close();
        }
        pieceBoard->handleEvent(sfEvent, mousePos, 0);
    }
}

void Chess::update() {
    pieceBoard->update();
}

void Chess::render() {
    mWindow.clear(sf::Color::Red);
    pieceBoard->render(mWindow, sf::RenderStates::Default);
    mWindow.display();
}