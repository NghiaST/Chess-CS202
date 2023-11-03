#include "IngameScreen.hpp"

IngameScreen::IngameScreen() {
    shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment);
    state.shader = &shader;
    // shader.setUniform("texture", sf::Shader::CurrentTexture);
    theme = new Theme();
    // theme->loadFile();
    srand(time(NULL));
    theme->setTheme(1);
    // theme->setTheme(rand() % 10);

    boardSize = Point(64, 64) * 8;
    buttonSize = Point(150, 70);
    boardPosition = Point(100, INTERFACE::WINDOWSIZE.y / 2 - boardSize.y / 2);

    timeButtonPosition = Point(boardPosition.x / 2, boardPosition.y + boardSize.y / 2);
    
    int leftPositionButton = INTERFACE::WINDOWSIZE.x - buttonSize.x - 2;
    saveButtonPosition    = Point(leftPositionButton, 1.05 * buttonSize.y);
    undoButtonPosition    = Point(leftPositionButton, 2.10 * buttonSize.y);
    redoButtonPosition    = Point(leftPositionButton, 3.15 * buttonSize.y);
    newgameButtonPosition = Point(leftPositionButton, 4.20 * buttonSize.y);
    exitButtonPosition    = Point(leftPositionButton, 5.25 * buttonSize.y);

    board = new Board(boardPosition, boardSize, theme);
    timeButton    = new Button(50, timeButtonPosition   , Point(40, 40), true , true, &theme->getFont(), Color::ColorButMultiGreen, 20, "Time");
    saveButton    = new Button(51, saveButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getButtonColorMulti(), 20, "Save");
    undoButton    = new Button(52, undoButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getButtonColorMulti(), 20, "Undo");
    redoButton    = new Button(53, redoButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getButtonColorMulti(), 20, "Redo");
    newgameButton = new Button(54, newgameButtonPosition, buttonSize   , false, true, &theme->getFont(), theme->getButtonColorMulti(), 20, "New Game");
    exitButton    = new Button(55, exitButtonPosition   , buttonSize   , false, true, &theme->getFont(), theme->getButtonColorMulti(), 20, "Exit"); 

    isPieceHold = false;
    mousePosition = Point(0, 0);

    defaultPriority = {
        {"board", 0},
        {"time", 1},
        {"save", 2},
        {"undo", 3},
        {"redo", 4},
        {"newgame", 5},
        {"exit", 6}
    };
    priority = defaultPriority;
    handleOrder = {
        "board",
        "time",
        "save",
        "undo",
        "redo",
        "newgame",
        "exit"
    };
}

IngameScreen::~IngameScreen() {
    delete theme;
    delete board;
    delete timeButton;
    delete saveButton;
    delete undoButton;
    delete redoButton;
    delete newgameButton;
    delete exitButton;
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
        if (name == "board") {
            status = board->handleEvent(event);
        }
        else if (name == "time") {
            status = timeButton->handleEvent(event) ? "time" : "";
        }
        else if (name == "save") {
            status = saveButton->handleEvent(event) ? "save" : "";
        }
        else if (name == "undo") {
            status = undoButton->handleEvent(event) ? "undo" : "";
            if (status == "undo") {
                board->UndoMove();
                if (board->getTurn() != CHESS::COLOR::WHITE) {
                    board->UndoMove();
                }
            }
        }
        else if (name == "redo") {
            status = redoButton->handleEvent(event) ? "redo" : "";
        }
        else if (name == "newgame") {
            status = newgameButton->handleEvent(event) ? "newgame" : "";
            if (status == "newgame") {
                board->NewGame();
            }
        }
        else if (name == "exit") {
            status = exitButton->handleEvent(event) ? "exit" : "";
        }
    }
}

void IngameScreen::update(sf::Time deltaTime) {
    std::string status = "";
    std::vector<std::string> updateOrder = {
        "board", "time", "save", "undo", "redo", "newgame", "exit"
    };

    for(std::string name : updateOrder) {
        if (name == "time") {
            // timeButton.update(deltaTime);
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

    board->updateRender();
    
    timeButton->updateRender();
    saveButton->updateRender();
    undoButton->updateRender();
    redoButton->updateRender();
    newgameButton->updateRender();
    exitButton->updateRender();
}

void IngameScreen::render(sf::RenderTarget& target, sf::RenderStates state) const {
    board->render(target, state);
    target.draw(*timeButton);
    target.draw(*saveButton);
    target.draw(*undoButton);
    target.draw(*redoButton);
    target.draw(*newgameButton);
    target.draw(*exitButton);
}