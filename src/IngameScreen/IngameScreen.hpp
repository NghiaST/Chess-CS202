#ifndef __IngameScreen_hpp__
#define __IngameScreen_hpp__

#include <SFML/Graphics.hpp>
#include "Board.hpp"

class IngameScreen {
public:
    IngameScreen();
    ~IngameScreen();
    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const;

private:
    // Process
    Point boardPosition;
    Point timeButtonPosition;
    Point saveButtonPosition;
    Point undoButtonPosition;
    Point redoButtonPosition;
    Point newgameButtonPosition;
    Point exitButtonPosition;

    Point boardSize;
    Point buttonSize;

private:
    sf::Shader shader;
    sf::RenderStates state;
    Theme* theme;

    Board* board;
    Button* timeButton;
    Button* saveButton;
    Button* undoButton;
    Button* redoButton;
    Button* newgameButton;
    Button* exitButton;

    bool isPieceHold;
    Point mousePosition;

    /// @brief default priority for handleEvent, smaller run first
    /// the smaller the number, the higher the priority to print upper
    std::map<std::string, int> defaultPriority;
    std::map<std::string, int> priority;
    std::vector<std::string> handleOrder;
};

#endif