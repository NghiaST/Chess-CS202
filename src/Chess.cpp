#include "Chess.hpp"

Chess::Chess() {
    event = new Event();
    pieceBoard = new PieceBoard();

    windowSize = Point(1000, 650);
    windowPosition = sf::Vector2i(200, 10);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    mWindow.create(sf::VideoMode(windowSize.x, windowSize.y), "ChessLion", sf::Style::Default, settings);
    mWindow.setFramerateLimit(60);
    mWindow.setPosition(windowPosition);
}

Chess::~Chess() {
    delete event;
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
        event->processEvents(sfEvent);
        pieceBoard->handleEvent(event);
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