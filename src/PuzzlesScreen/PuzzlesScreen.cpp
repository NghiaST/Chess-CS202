#include <PuzzlesScreen/PuzzlesScreen.hpp>

PuzzlesScreen::PuzzlesScreen() : Screen() {
    currentScreen = ScreenType::PuzzlesScreen;
    BitboardUtility::Initialize();
    
    boardSize = Point(64, 64) * 8;
    buttonSize = Point(150, 70);
    timeButtonSize = Point(80, 40);
    boardPosition = Point(100, INTERFACE::WindowSize.y / 2 - boardSize.y / 2);

    timeButtonPosition = Point(boardPosition.x / 2, boardPosition.y + boardSize.y / 2);
    int leftPositionButton = INTERFACE::WindowSize.x - buttonSize.x - 2;
    
    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    saveButtonPosition        = Point(leftPositionButton, 1.05 * buttonSize.y);
    undoButtonPosition        = Point(leftPositionButton, 2.10 * buttonSize.y);
    redoButtonPosition        = Point(leftPositionButton, 3.15 * buttonSize.y);
    newPuzzleButtonPosition   = Point(leftPositionButton, 4.20 * buttonSize.y);
    backButtonPosition        = Point(leftPositionButton, 5.25 * buttonSize.y);
    hintButtonPosition        = Point(leftPositionButton, 8.30 * buttonSize.y);
    autoRestartOptionPosition = Point(leftPositionButton, 7 * buttonSize.y);

    Point timeButtonPositionWhite = boardPosition + boardSize - Point(timeButtonSize.x, 0) + Point(0, 5);
    Point timeButtonPositionBlack = boardPosition + Point(boardSize.x, 0) - timeButtonSize - Point(0, 5);

    boardPuzzlesManager = new BoardPuzzlesManager(boardPosition, boardSize);
    timeButton = new TimeButton(50, timeButtonPositionWhite, timeButtonPositionBlack, timeButtonSize, &theme->getFont(), theme->getColorDefault());
    saveButton    = new Button(51, saveButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Save");
    undoButton    = new Button(52, undoButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Undo");
    redoButton    = new Button(53, redoButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Redo");
    newPuzzleButton = new Button(54, newPuzzleButtonPosition, buttonSize, false, true, &theme->getFont(), theme->getColorDefault(), 20, "New Puzzle");
    backButton    = new Button(55, backButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Back");
    hintButton    = new Button(55, hintButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Hint");
    autoRestartOption = new ButtonOption(56, autoRestartOptionPosition, buttonSize, false, true, &theme->getFont(), theme->getColorDefault(), 10, {"Off", "On"});
    notificationEndGame = new NotificationEndGame(0, Point(INTERFACE::WindowSize) / 2, Point(300, 300), true, true, &theme->getFont(), 1, "");
    notificationEndGame->setIsPrint(false);
    timeButton->setReverseTable(boardPuzzlesManager->isBoardRotate());

    isPieceHold = false;
    mousePosition = Point(0, 0);

    defaultPriority = {
        {"boardManager", 0},
        {"time", 1},
        {"save", 2},
        {"undo", 3},
        {"redo", 4},
        {"newPuzzle", 5},
        {"back", 6},
        {"hint", 7},
        {"autoRestartOption", 8},
        {"notificationEndGame", -1}
    };
    priority = defaultPriority;
    handleOrder = {
        "notificationEndGame",
        "boardManager",
        "time",
        "save",
        "undo",
        "redo",
        "newPuzzle",
        "back",
        "hint",
        "autoRestartOption"
    };
}

PuzzlesScreen::~PuzzlesScreen() {
    delete boardPuzzlesManager;
    delete timeButton;
    delete saveButton;
    delete undoButton;
    delete redoButton;
    delete newPuzzleButton;
    delete backButton;
    delete hintButton;
    delete autoRestartOption;
    delete notificationEndGame;
}

void PuzzlesScreen::handleEvent(const sf::Event& event) {
    /** 
     * status = 00: no event,
     *          01: piece is hold,
     *          02: piece is moved, 
     *          03: illegal move
     *          04: undo move
     *          05: redo move
     *          10: checkmate,
     *          11: stalemate
     * 
     *          20: new game
     *          21: save game
    */
    std::sort(handleOrder.begin(), handleOrder.end(), [&] (std::string a, std::string b) {
        return priority[a] < priority[b];
    });

    std::string status = "";
    for(std::string name : handleOrder) {
        if (status != "") break;
        if (name == "boardManager") {
            status = boardPuzzlesManager->handleEvent(event);
            if (status == "make move") {
                if (boardPuzzlesManager->isEndQuiz()) {
                    status = "end game";
                    if (boardPuzzlesManager->isAutoRestart() == false)
                        notificationEndGame->setEndGame("Puzzle Solved!", boardPuzzlesManager->getQuizName() + "\n" + boardPuzzlesManager->getQuizLink());
                }
            }
        }
        else if (name == "time") {
            // status = timeButton->handleEvent(event) ? "time" : "";
        }
        else if (name == "save") {
            status = saveButton->handleEvent(event) ? "save" : "";
            if (status == "save") {
                FileManager::ExtractGame(boardPuzzlesManager->getBoard().getMovesHistory());
            }
        }
        else if (name == "undo") {
            status = undoButton->handleEvent(event) ? "undo" : "";
            if (status == "undo") {
                boardPuzzlesManager->Undo();
            }
        }
        else if (name == "redo") {
            status = redoButton->handleEvent(event) ? "redo" : "";
            if (status == "redo") {
                boardPuzzlesManager->Redo();
            }
        }
        else if (name == "newPuzzle") {
            status = newPuzzleButton->handleEvent(event) ? "newPuzzle" : "";
            if (status == "newPuzzle") {
                boardPuzzlesManager->NewQuiz();
                timeButton->setReverseTable(boardPuzzlesManager->isBoardRotate());
            }
        }
        else if (name == "back") {
            status = backButton->handleEvent(event) ? "back" : "";
            if (status == "back") {
                isScreenChange = true;
                nextScreen = ScreenType::HomeScreen;
            }
        }
        else if (name == "hint") {
            status = hintButton->handleEvent(event) ? "hint" : "";
            if (status == "hint") {
                boardPuzzlesManager->setIsShowSolution(true);
            }
        }
        else if (name == "autoRestartOption") {
            status = autoRestartOption->handleEvent(event) ? "autoRestartOption" : "";
            if (status == "autoRestartOption") {
                if (autoRestartOption->getCurrentSelection() == 0) {
                    boardPuzzlesManager->setAutoRestart(false);
                }
                else {
                    boardPuzzlesManager->setAutoRestart(true);
                }
            }
        }
        else if (name == "notificationEndGame") {
            status = notificationEndGame->handleEvent(event) ? "notificationEndGame" : "";
            if (status == "notificationEndGame") {
                if (notificationEndGame->getOnclick() == NotificationEndGame::Onclick::NEW_GAME) {
                    boardPuzzlesManager->NewQuiz();
                    timeButton->setReverseTable(boardPuzzlesManager->isBoardRotate());
                }
                else if (notificationEndGame->getOnclick() == NotificationEndGame::Onclick::BACK) {
                    isScreenChange = true;
                    nextScreen = ScreenType::HomeScreen;
                }
                else if (notificationEndGame->getOnclick() == NotificationEndGame::Onclick::CLOSE) {
                    notificationEndGame->setIsPrint(false);
                }
            }
        }
    }
}

void PuzzlesScreen::update(sf::Time deltaTime) {
    std::string status = "";
    std::vector<std::string> updateOrder = {
        "boardManager", "time", "save", "undo", "redo", "newPuzzle", "back"
    };

    for(std::string name : updateOrder) {
        if (name == "time") {
            // timeButton->update(deltaTime);
        }
        else if (name == "boardManager") {
            status = boardPuzzlesManager->update(deltaTime);

            if (status == "make move") {
                if (boardPuzzlesManager->isEndQuiz()) {
                    status = "end game";
                    if (boardPuzzlesManager->isAutoRestart() == false)
                        notificationEndGame->setEndGame("Puzzle Solved!", boardPuzzlesManager->getQuizLink());
                }
            }

            timeButton->update(*boardPuzzlesManager);
        }
        if (status == "" || status == "no event") {
            // no event: do nothing
        }
        else if (status == "out of time") {
            // do something
        }
        else {
            // default: do nothing
        }
    }
    boardPuzzlesManager->updateRender();
}

void PuzzlesScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    target.draw(Background);
    target.draw(*saveButton);
    target.draw(*undoButton);
    target.draw(*redoButton);
    target.draw(*newPuzzleButton);
    target.draw(*backButton);
    target.draw(*hintButton);
    target.draw(*autoRestartOption);
    timeButton->draw(target);
    boardPuzzlesManager->draw(target, states);
    notificationEndGame->draw(target);
}

void PuzzlesScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    saveButton->setColorBM(theme->getColorDefault());
    undoButton->setColorBM(theme->getColorDefault());
    redoButton->setColorBM(theme->getColorDefault());
    newPuzzleButton->setColorBM(theme->getColorDefault());
    backButton->setColorBM(theme->getColorDefault());
    hintButton->setColorBM(theme->getColorDefault());
    timeButton->setColorBM(theme->getColorDefault());
    autoRestartOption->setColorBM(theme->getColorDefault());
}