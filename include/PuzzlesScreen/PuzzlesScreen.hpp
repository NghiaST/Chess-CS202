#ifndef __PuzzlesScreen_hpp__
#define __PuzzlesScreen_hpp__

#include <Screen.hpp>
#include <PuzzlesScreen/BoardPuzzlesManager.hpp>
#include <IngameScreen/TimeButton.hpp>
#include <DataControl/ButtonOption.hpp>
#include <DataControl/Image.hpp>
#include <IngameScreen/NotificationEndGame.hpp>
#include <SFML/Graphics.hpp>

class PuzzlesScreen : public Screen {
public:
    PuzzlesScreen();
    ~PuzzlesScreen();
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
    Point newPuzzleButtonPosition;
    Point backButtonPosition;
    Point hintButtonPosition;
    Point autoRestartOptionPosition;

    Point boardSize;
    Point buttonSize;
    Point timeButtonSize;
    Point autoRestartOptionSize;

private:
    BoardPuzzlesManager* boardPuzzlesManager;
    TimeButton* timeButton;
    
    Image Background;
    Button* saveButton;
    Button* undoButton;
    Button* redoButton;
    Button* newPuzzleButton;
    Button* backButton;
    Button* hintButton;
    ButtonOption* autoRestartOption;
    NotificationEndGame* notificationEndGame;

    bool isPieceHold;
    Point mousePosition;

    /// @brief default priority for handleEvent, smaller run first
    /// the smaller the number, the higher the priority to print upper
    std::map<std::string, int> defaultPriority;
    std::map<std::string, int> priority;
    std::vector<std::string> handleOrder;
};

#endif