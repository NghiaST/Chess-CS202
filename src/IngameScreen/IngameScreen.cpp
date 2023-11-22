#include <IngameScreen/IngameScreen.hpp>

IngameScreen::IngameScreen() : Screen() {
    currentScreen = ScreenType::IngameScreen;
    BitboardUtility::Initialize();
    
    boardSize = Point(64, 64) * 8;
    buttonSize = Point(150, 70);
    timeButtonSize = Point(80, 40);
    boardPosition = Point(100, INTERFACE::WindowSize.y / 2 - boardSize.y / 2);

    timeButtonPosition = Point(boardPosition.x / 2, boardPosition.y + boardSize.y / 2);
    int leftPositionButton = INTERFACE::WindowSize.x - buttonSize.x - 2;
    
    Background = Image(theme->getBackgroundTexture(), Point(0, 0), INTERFACE::WindowSize, true, 0);
    saveButtonPosition    = Point(leftPositionButton, 1.05 * buttonSize.y);
    undoButtonPosition    = Point(leftPositionButton, 2.10 * buttonSize.y);
    redoButtonPosition    = Point(leftPositionButton, 3.15 * buttonSize.y);
    newgameButtonPosition = Point(leftPositionButton, 4.20 * buttonSize.y);
    backButtonPosition    = Point(leftPositionButton, 5.25 * buttonSize.y);
    autoRestartOptionPosition = Point(leftPositionButton, 7 * buttonSize.y);

    Point timeButtonPositionWhite = boardPosition + boardSize - Point(timeButtonSize.x, 0) + Point(0, 5);
    Point timeButtonPositionBlack = boardPosition + Point(boardSize.x, 0) - timeButtonSize - Point(0, 5);

    boardManager = new BoardManager(boardPosition, boardSize);
    timeButton = new TimeButton(50, timeButtonPositionWhite, timeButtonPositionBlack, timeButtonSize, &theme->getFont(), theme->getColorDefault());
    saveButton    = new Button(51, saveButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Save");
    undoButton    = new Button(52, undoButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Undo");
    redoButton    = new Button(53, redoButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Redo");
    newgameButton = new Button(54, newgameButtonPosition, buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "New Game");
    backButton    = new Button(55, backButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getColorDefault(), 20, "Back"); 
    autoRestartOption = new ButtonOption(56, autoRestartOptionPosition, buttonSize, false, true, &theme->getFont(), theme->getColorDefault(), 10, {"Off", "On"});
    timeButton->setReverseTable(boardManager->ifBoardRotate());

    isPieceHold = false;
    mousePosition = Point(0, 0);

    defaultPriority = {
        {"boardManager", 0},
        {"time", 1},
        {"save", 2},
        {"undo", 3},
        {"redo", 4},
        {"newgame", 5},
        {"back", 6},
        {"autoRestartOption", 7}
    };
    priority = defaultPriority;
    handleOrder = {
        "boardManager",
        "time",
        "save",
        "undo",
        "redo",
        "newgame",
        "back",
        "autoRestartOption"
    };
}

IngameScreen::~IngameScreen() {
    delete boardManager;
    delete timeButton;
    delete saveButton;
    delete undoButton;
    delete redoButton;
    delete newgameButton;
    delete backButton;
    delete autoRestartOption;
}

void IngameScreen::handleEvent(const sf::Event& event) {
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
            status = boardManager->handleEvent(event);
            if (status == "make move") {
                timeButton->setTurn(boardManager->getTurn());
                timeButton->setIsCountDown(true);
                if (boardManager->ifEndGame()) {
                    timeButton->setIsCountDown(false);
                    if (boardManager->isCheckMate()) {
                        status = "checkmate";
                    }
                    else if (boardManager->ifStaleMate()) {
                        status = "stalemate";
                    }
                }
            }
        }
        else if (name == "time") {
            // status = timeButton->handleEvent(event) ? "time" : "";
        }
        else if (name == "save") {
            status = saveButton->handleEvent(event) ? "save" : "";
            if (status == "save") {
                FileInit::ExtractGame(boardManager->getBoard().getMovesHistory());
            }
        }
        else if (name == "undo") {
            status = undoButton->handleEvent(event) ? "undo" : "";
            if (status == "undo") {
                boardManager->Undo();
            }
        }
        else if (name == "redo") {
            status = redoButton->handleEvent(event) ? "redo" : "";
            if (status == "redo") {
                boardManager->Redo();
            }
        }
        else if (name == "newgame") {
            status = newgameButton->handleEvent(event) ? "newgame" : "";
            if (status == "newgame") {
                boardManager->NewGame();
                timeButton->setReverseTable(boardManager->ifBoardRotate());
            }
        }
        else if (name == "back") {
            status = backButton->handleEvent(event) ? "back" : "";
            if (status == "back") {
                isScreenChange = true;
                nextScreen = ScreenType::HomeScreen;
            }
            // if (status == "newgame") {
            //     boardManager->NewGame();
            //     timeButton->reset();
            // }
        }
        else if (name == "autoRestartOption") {
            status = autoRestartOption->handleEvent(event) ? "autoRestartOption" : "";
            if (status == "autoRestartOption") {
                if (autoRestartOption->getCurrentSelection() == 0) {
                    boardManager->setAutoRestart(false);
                }
                else {
                    boardManager->setAutoRestart(true);
                }
            }
        }
    }
}

void IngameScreen::update(sf::Time deltaTime) {
    std::string status = "";
    std::vector<std::string> updateOrder = {
        "boardManager", "time", "save", "undo", "redo", "newgame", "back"
    };

    for(std::string name : updateOrder) {
        if (name == "time") {
            // timeButton->update(deltaTime);
        }
        else if (name == "boardManager") {
            status = boardManager->update(deltaTime);

            if (status == "make move") {
                if (boardManager->ifEndGame()) {
                    if (boardManager->isCheckMate()) {
                        status = "checkmate";
                    }
                    else if (boardManager->ifStaleMate()) {
                        status = "stalemate";
                    }
                }
            }

            timeButton->update(*boardManager);
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
    boardManager->updateRender();
}

void IngameScreen::render(sf::RenderTarget& target, sf::RenderStates states) {
    target.draw(Background);
    target.draw(*saveButton);
    target.draw(*undoButton);
    target.draw(*redoButton);
    target.draw(*newgameButton);
    target.draw(*backButton);
    target.draw(*autoRestartOption);
    timeButton->draw(target);
    boardManager->draw(target, states);
}

void IngameScreen::formatTheme() {
    Background.setTexture(theme->getBackgroundTexture());
    saveButton->setColorBM(theme->getColorDefault());
    undoButton->setColorBM(theme->getColorDefault());
    redoButton->setColorBM(theme->getColorDefault());
    newgameButton->setColorBM(theme->getColorDefault());
    backButton->setColorBM(theme->getColorDefault());
    timeButton->setColorBM(theme->getColorDefault());
    autoRestartOption->setColorBM(theme->getColorDefault());
}