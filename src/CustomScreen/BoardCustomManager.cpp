#include <CustomScreen/BoardCustomManager.hpp>

BoardCustomManager::BoardCustomManager(Point renderPosition, Point renderSize) 
    : GameAttributes() {
    // Load Theme
    theme = Theme::getInstance();

    // Load Shader
    shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment);
    state.shader = &shader;

    // Load Board
    board = FactoryBoard::CreateBoard(GameAttributes::getVariantsName());
    board->LoadBasicPosition();

    // Load BoardPrint
    boardPosition = renderPosition;
    boardSize = renderSize;
    boardPrint = new BoardPrint(boardPosition, boardSize, &theme->getTextureBoard());
    boardPrint->update();

    // Load PiecePrint
    cellSize = boardSize / 8;
    piecePrintList.assign(64, nullptr);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        int index = std::distance(piecePrintList.begin(), it);
        *it = new PiecePrint(this->boardPosition, this->cellSize, index, board->getPiece(index));
    }

    // Load ButtonPieceGroup
    buttonPieceGroup = new ButtonPieceGroup(Point(610, 100));

    // Load pieces
    setDefault();
}

BoardCustomManager::~BoardCustomManager() {
    delete board;
    delete boardPrint;
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        delete *it;
    }
    delete buttonPieceGroup;
}

const Board* BoardCustomManager::getBoard() const {
    return board;
}

std::string BoardCustomManager::handleEvent(const sf::Event& event) {
    std::string res = "";
    if (event.type == sf::Event::MouseMoved) {
        mousePosition = Point(event.mouseMove.x, event.mouseMove.y);
    }
    buttonPieceGroup->handleEvent(event);
    if (buttonPieceGroup->isPieceReleased()) {
        int piece = buttonPieceGroup->getPieceReleased();
        if (boardPrint->isMouseOn(mousePosition)) {
            int squareIndex = boardPrint->getMouseIndex(mousePosition, true);
            board->setPiece(squareIndex, piece);
            piecePrintList[squareIndex]->setPiece(piece);
            updateRender();
        }
    }
    else {
        for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
            if ((*it)->handleEvent(event)) {
                int piece = (*it)->getPiece();
                int square = std::distance(piecePrintList.begin(), it);
                board->setPiece(square, PIECE::None);
                (*it)->setPiece(PIECE::None);
                if (piece)
                    buttonPieceGroup->TurnOnPiece(piece);
            }
        }
        updateRender();
    }

    return res;
}

std::string BoardCustomManager::update(sf::Time deltaTime) {
    return "";
}

void BoardCustomManager::updateRender() {
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->setPiece(board->getPiece(i));
        piecePrintList[i]->setMouseStatus(MOUSE::None);
        boardPrint->setStateCell(i, BoardPrint::Common);
    }
}
void BoardCustomManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*boardPrint);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        target.draw(**it);
    }
    target.draw(*buttonPieceGroup);
}

void BoardCustomManager::setDefault() {
    board->LoadBasicPosition();
    updateRender();
}

void BoardCustomManager::setClean() {
    board->LoadPosition("8/8/8/8/8/8/8/8 w KQkq - 0 1");
    updateRender();
}

bool BoardCustomManager::isCustomBoardValid() {
    return board->isBoardValidByCustom();
}