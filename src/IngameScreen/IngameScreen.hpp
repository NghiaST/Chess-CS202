#ifndef __IngameScreen_hpp__
#define __IngameScreen_hpp__

#include <SFML/Graphics.hpp>
#include "BoardManager.hpp"
#include "TimeButton.hpp"
#include "../Screen.hpp"
#include "../DataControl/Image.hpp"

class IngameScreen : public Screen {
public:
    IngameScreen();
    ~IngameScreen();
    void handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) override;

    void formatTheme() override;
    
private:
    // Process
    Point boardPosition;
    Point timeButtonPosition;
    Point saveButtonPosition;
    Point undoButtonPosition;
    Point redoButtonPosition;
    Point newgameButtonPosition;
    Point backButtonPosition;

    Point boardSize;
    Point buttonSize;
    Point timeButtonSize;

private:
    BoardManager* boardManager;
    TimeButton* timeButton;
    
    Image Background;
    Button* saveButton;
    Button* undoButton;
    Button* redoButton;
    Button* newgameButton;
    Button* backButton;

    bool isPieceHold;
    Point mousePosition;

    /// @brief default priority for handleEvent, smaller run first
    /// the smaller the number, the higher the priority to print upper
    std::map<std::string, int> defaultPriority;
    std::map<std::string, int> priority;
    std::vector<std::string> handleOrder;
};

#endif