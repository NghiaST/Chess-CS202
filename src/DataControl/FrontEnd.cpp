#include "FrontEnd.hpp"

FrontEnd::FrontEnd() {
    theme = new Theme();
    windowSize = Point(1000, 650);
    mousePos = Point(0, 0);
    mouseStatus = 0;
    timeMousePress = 0;
    clock.restart();
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    window = new sf::RenderWindow(sf::VideoMode(windowSize.x, windowSize.y), "ChessLion", sf::Style::Default, settings);
    window->setFramerateLimit(60);
    window->setPosition(sf::Vector2i(200, 10));
}

FrontEnd::~FrontEnd() {
    delete theme;
    delete window;
}

void FrontEnd::setTheme(const ThemeIndex themeIndex) {
    theme->setTheme(themeIndex);
}

void FrontEnd::setMouseStatus(int mouseStatus) {
    this->mouseStatus = mouseStatus;
}

void FrontEnd::setMousePos(int x, int y) {
    mousePos.x = x;
    mousePos.y = y;
}

void FrontEnd::setMousePos(Point mousePos) {
    this->mousePos = mousePos;
}

void FrontEnd::setWindowSize(int windowWidth, int windowHeight) {
    windowSize.x = windowWidth;
    windowSize.y = windowHeight;
}

void FrontEnd::setWindow(sf::RenderWindow* window) {
    this->window = window;
}

void FrontEnd::setTimeMousePress(double timeMousePress) {
    this->timeMousePress = timeMousePress;
}

const Point& FrontEnd::getMousePos() const {
    return mousePos;
}

const Theme* FrontEnd::getTheme() const {
    return theme;
}

sf::RenderWindow* FrontEnd::getWindow() const {
    return window;
}

bool FrontEnd::isRunning() const
{
    return window->isOpen();
}

void FrontEnd::processEvents()
{
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            mouseStatus = 1;
            timeMousePress = clock.getElapsedTime().asSeconds();
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            mouseStatus = 3;
        }
        if (event.type == sf::Event::MouseMoved) {
            mousePos.x = event.mouseMove.x;
            mousePos.y = event.mouseMove.y;
        }
        clock.restart();
    }
}

void FrontEnd::print() {
    window->display();
    window->clear(sf::Color::Red);
}