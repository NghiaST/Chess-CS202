#include <PuzzlesScreen/BoardPuzzlesManager.hpp>
#include <Helpers/MoveUtility.hpp>

BoardPuzzlesManager::BoardPuzzlesManager(Point renderPosition, Point renderSize) 
    : GameAttributes(0, 0, 0, -1, -1, false)
{
    board = FactoryBoard::CreateBoard("standard");
    theme = Theme::getInstance();
    promotionManager = new PromotionManager(0, renderPosition, renderSize);
    mIsAutoRestart = false;

    if (!shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment)) {
        printf("Error loading shader\n");
    }
    state.shader = &shader;
    this->theme = theme;
    this->boardPosition = renderPosition;
    this->boardSize = renderSize;
    this->cellSize = boardSize / 8;

    piecePrintList.assign(64, nullptr);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        int index = std::distance(piecePrintList.begin(), it);
        *it = new PiecePrint(this->boardPosition, this->cellSize, index, PIECE::None);
    }
    boardPrint = new BoardPrint(boardPosition, boardSize, &theme->getTextureBoard());
    gameStatus = GAMESTATUS::NONSTART;

    // load game
    NewQuiz();
}

BoardPuzzlesManager::~BoardPuzzlesManager() {
    delete board;
    delete boardPrint;
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        delete *it;
    }
}

bool BoardPuzzlesManager::isBoardRotate() const {
    return mIsBoardRotate;
}

// Accessors
int BoardPuzzlesManager::getGameStatus() const {
    return (int) gameStatus;
}
CHESS::COLOR BoardPuzzlesManager::getTurn() const {
    return CHESS::COLOR(mIsWhiteTurn);
}

bool BoardPuzzlesManager::isBotTurn() const {
    return isBot[mIsWhiteTurn];
}

bool BoardPuzzlesManager::isCheckMate() const {
    return mIsCheckMate;
}

bool BoardPuzzlesManager::isStaleMate() const {
    return mIsStaleMate;
}

bool BoardPuzzlesManager::isEndQuiz() const {
    return cntMoves == (int) movesSolution.size();
}

const Board &BoardPuzzlesManager::getBoard() const {
    return *board;
}

std::string BoardPuzzlesManager::getQuizName() const {
    return quizName;
}
std::string BoardPuzzlesManager::getQuizLink() const {
    return quizLink;
}

bool BoardPuzzlesManager::isAutoRestart() const {
    return mIsAutoRestart;
}

// Modifiers
void BoardPuzzlesManager::freshState() {
    mIsShowSolution = false;
    mIsCheck = board->isCheck();
    mIsCheckMate = board->isCheckMate();
    mIsStaleMate = board->isStaleMate();
    mIsWhiteTurn = board->isWhiteTurn();
    mIsEvent = true;
    isPieceSelected = false;
    isNoteHold = false;
    isPiecePromotion = false;
    noteList.clear();
    promotionManager->setPromotionFile(-1);
    promotionManager->setIsRotate(mIsBoardRotate);
    promotionManager->setIsWhite(mIsWhiteTurn);
    setTurn(mIsWhiteTurn);

    if (isEndQuiz()) {
        gameStatus = ENDGAME;
    }
    if (gameStatus == NONSTART) {
        gameStatus = ONGOING;
    }
}

void BoardPuzzlesManager::setBoardRotate(bool mIsBoardRotate) {
    this->mIsBoardRotate = mIsBoardRotate;
    boardPrint->setBoardRotate(mIsBoardRotate);
    for(int i = 0; i < 64; i++) {
        int index = mIsBoardRotate ? 63 - i : i;
        piecePrintList[i]->setIndex(index);
    }
}

void BoardPuzzlesManager::NewQuiz() {
    int index = rand() % 5000;
    printf("Quiz index: %d\n", index);
    FileManager::LoadPuzzles(*board, movesSolution, quizName, quizLink, index);
    setMode(board->isWhiteTurn());
    Reload();
}

void BoardPuzzlesManager::Reload() {
    Fresh();
    switch (mode) {
        case 0: 
            isBot = {true, false};
            break;
        case 1:
            isBot = {false, true};
            break;
        case 2:
            isBot = {false, false};
            break;
        case 3:
            isBot = {true, true};
            break;
        default:
            isBot = {false, false};
            break;
    }

    mIsShowSolution = false;
    cntMoves = 0;
    setBoardRotate(!isPlayerWhite);
    gameStatus = GAMESTATUS::NONSTART;
    isPieceSelected = false;
    isPieceHold = false;
    selectedPieceIndex = -1;
    preSquareIndex = -1;
    curSquareIndex = -1;
    freshState();

    setCountDown(false);
}

void BoardPuzzlesManager::Undo() {
    if (!board->UndoMoveCache()) return;
    --cntMoves;
    freshState();

    if (isBot[mIsWhiteTurn] == false || gameStatus == ENDGAME) return;
    if (!board->UndoMoveCache()) return;
    --cntMoves;
    freshState();
}

void BoardPuzzlesManager::Redo() {
    if (!board->RedoMoveCache()) return;
    ++cntMoves;
    freshState();

    if (isBot[mIsWhiteTurn] == false || gameStatus == ENDGAME) return;
    if (!board->RedoMoveCache()) return;
    ++cntMoves;
    freshState();
}

void BoardPuzzlesManager::setBotHelp(bool isBotHelp) {
    this->isBotHelp = isBotHelp;
    mIsEvent = true;
}

void BoardPuzzlesManager::setAutoRestart(bool isAutoRestart) {
    this->mIsAutoRestart = isAutoRestart;
}

void BoardPuzzlesManager::setIsShowSolution(bool isShowSolution) {
    this->mIsShowSolution = isShowSolution;
    mIsEvent = true;
}

void BoardPuzzlesManager::MakeCorrectMove(Move move) {
    if (!(move == movesSolution[cntMoves])) {
        std::cout << move.startSquare << ' ' << move.targetSquare << ' ' << move.flag << ' ' << movesSolution[cntMoves].startSquare << ' ' << movesSolution[cntMoves].targetSquare << ' ' << movesSolution[cntMoves].flag << '\n';
        std::cout << "Wrong move\n";
        freshState();
        return;
    }
    std::cout << MoveUtility::GetMoveNameSAN(move, *board) << '\n';
    board->MoveCache(move);
    GameAttributes::updateMakeMove();
    isPieceSelected = false;
    isPieceHold = false;
    preSquareIndex = move.startSquare;
    curSquareIndex = move.targetSquare;
    ++cntMoves;
    freshState();
}

bool BoardPuzzlesManager::ManageMove(int startSquare, int targetSquare, bool isBotMove)
{
    if (!isBotMove && isBot[mIsWhiteTurn]) return false;
    std::vector<Move> moveList = board->GenerateMovesSquare(startSquare);
    for(Move move : moveList) {
        if (move.targetSquare == targetSquare) {
            if (move.isPromotion()) {
                movePromotion = move;
                promotionManager->setPromotionFile(targetSquare % 8);
                promotionManager->setIsWhite(mIsWhiteTurn);
                isPiecePromotion = true;
                return false;
            }
            MakeCorrectMove(move);
            return true;
        }
    }
    return false;
}

std::vector<int> BoardPuzzlesManager::getLegalIndexAt(int squareIndex) {
    std::vector<int> legalIndexs;
    std::vector<Move> legalMoves = board->GenerateMovesSquare(squareIndex);
    for(Move move : legalMoves)
        legalIndexs.push_back(move.targetSquare);
    return legalIndexs;
}

bool BoardPuzzlesManager::isMovePromotion(int startSquare, int targetSquare) {
    if (board->getPiece(startSquare) == PIECE::Pawn) {
        if (PIECE::PieceColor(board->getPiece(startSquare)) == PIECE::White) {
            if (targetSquare >= 56 && targetSquare <= 63) {
                return getLegalIndexAt(startSquare).size() > 0;
            }
        }
        else {
            if (targetSquare >= 0 && targetSquare <= 7) {
                return getLegalIndexAt(startSquare).size() > 0;
            }
        }
    }
    return false;
}

std::string BoardPuzzlesManager::handleEvent(const sf::Event& event) {
    mIsEvent = true;
    std::string res = "";
    if (isPiecePromotion) {
        if (promotionManager->handleEvent(event)) {
            int piecePromotionType = promotionManager->getPiecePromotionType();
            promotionManager->setPromotionFile(-1);
            movePromotion.setPromotionType(piecePromotionType);
            MakeCorrectMove(movePromotion);
            res = "make move";
        }
        else {
            if (event.type == sf::Event::MouseButtonPressed) {
                isPiecePromotion = false;
                isPieceSelected = false;
                isPieceHold = false;
                promotionManager->setPromotionFile(-1);
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        mousePosition = Point(event.mouseMove.x, event.mouseMove.y);
        if (isNoteHold) { 
            if (boardPrint->isMouseOn(mousePosition)) {
                sf::Vector2i coordChess;
                coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                int squareIndex = coordChess.x * 8 + coordChess.y;
                noteList.back().second = squareIndex;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        mousePosition = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (boardPrint->isMouseOn(mousePosition)) {
                noteList.clear();
                isNoteHold = false;
                if (gameStatus == NONSTART || gameStatus == ONGOING) {
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    if (mIsBoardRotate) {
                        coordChess.x = 7 - coordChess.x;
                        coordChess.y = 7 - coordChess.y;
                    }
                    int squareIndex = coordChess.x * 8 + coordChess.y;
                    if (!isPieceSelected) {
                        if (PIECE::isPieceYourTurn(board->getPiece(squareIndex), mIsWhiteTurn)) {
                            isPieceSelected = true;
                            isPieceHold = true;
                            selectedPieceIndex = squareIndex;
                            holdPieceIndex = squareIndex;
                            possibleIndexList = getLegalIndexAt(squareIndex);
                        }
                    }
                    else {
                        if (selectedPieceIndex == squareIndex) {
                            isPieceSelected = false;
                            isPieceHold = true;
                        }
                        else if (isMovePromotion(selectedPieceIndex, squareIndex)) {
                            isPiecePromotion = true;
                            movePromotion = Move(selectedPieceIndex, squareIndex, Move::NoFlag);
                            promotionManager->setPromotionFile(selectedPieceIndex);
                        }
                        else /// when click other pos
                        if (ManageMove(selectedPieceIndex, squareIndex)) {
                            res = "make move";
                        }
                        else if (isPiecePromotion) {}
                        else if (PIECE::PieceColor(board->getPiece(squareIndex)) == PIECE::boolToColor(mIsWhiteTurn)) {
                            isPieceSelected = true;
                            isPieceHold = true;
                            selectedPieceIndex = squareIndex;
                            holdPieceIndex = squareIndex;
                            possibleIndexList = getLegalIndexAt(squareIndex);
                        }
                        else {
                            isPieceSelected = false;
                        }
                    }
                }
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right) {
            if (boardPrint->isMouseOn(mousePosition)) {
                isPieceSelected = false;
                sf::Vector2i coordChess;
                coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                int squareIndex = coordChess.x * 8 + coordChess.y;
                noteList.emplace_back(squareIndex, squareIndex);
                isNoteHold =  true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (gameStatus == NONSTART || gameStatus == ONGOING) {
                if (boardPrint->isMouseOn(mousePosition)) {
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    if (mIsBoardRotate) {
                        coordChess.x = 7 - coordChess.x;
                        coordChess.y = 7 - coordChess.y;
                    }
                    int squareIndex = coordChess.x * 8 + coordChess.y;
                    if (isPieceHold) {
                        isPieceHold = false;
                        if (ManageMove(selectedPieceIndex, squareIndex)) {
                            res = "make move";
                        }
                    }
                }
                else {
                    isPieceHold = false;
                }
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right) {
            if (isNoteHold) {
                auto it = std::find(noteList.begin(), noteList.end(), noteList.back());
                if (it != noteList.end() - 1) {
                    noteList.erase(it);
                    noteList.pop_back();
                }   
                isNoteHold = false;
            }
        }
    }

    return res;
}

std::string BoardPuzzlesManager::update(sf::Time deltaTime) {
    if (gameStatus == ENDGAME) {
        if (mIsAutoRestart) {
            NewQuiz();
        }
        return "";
    }

    std::string res = "";
    if (gameStatus != ENDGAME) {
        if (isBot[mIsWhiteTurn]) {
            MakeCorrectMove(movesSolution[cntMoves]);
            res = "make move";
        }
    }
    /// logic (time)
    /*
        code something here
    */
    return res;
}

void BoardPuzzlesManager::updateRender() {
    if (!mIsEvent) return;
    mIsEvent = false;
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->setPiece(board->getPiece(i));
        piecePrintList[i]->setMouseStatus(MOUSE::None);
        boardPrint->setStateCell(i, BoardPrint::Common);
    }
    if (mIsCheck) {
        boardPrint->setStateCell(board->getKingSquareIndex(mIsWhiteTurn), BoardPrint::Check);
    }
    if (mIsCheckMate) {
        boardPrint->setStateCell(board->getKingSquareIndex(mIsWhiteTurn), BoardPrint::CheckMate);
    }
    if (mIsStaleMate) {
        boardPrint->setStateCell(board->getKingSquareIndex(mIsWhiteTurn), BoardPrint::StaleMate);
    }
    if (board->isHistoryEmpty() == false) {
        Move lastMove = board->getLastMove();
        boardPrint->setStateCell(lastMove.startSquare, BoardPrint::PreMoveStart);
        boardPrint->setStateCell(lastMove.targetSquare, BoardPrint::PreMoveTarget);
    }
    if (isPieceSelected | isPieceHold) {
        boardPrint->setStateCell(selectedPieceIndex, BoardPrint::Selected);
        for(int u : possibleIndexList) {
            if (board->getPiece(u) == PIECE::None)
                boardPrint->setStateCell(u, BoardPrint::Possible);
            else
                boardPrint->setStateCell(u, BoardPrint::PossibleCapture);
        }
    }
    if (isPieceHold) {
        boardPrint->setStateCell(holdPieceIndex, BoardPrint::Selected);
        piecePrintList[holdPieceIndex]->setMouseStatus(MOUSE::Hold, mousePosition);
    }

    noteCircleRender.clear();
    noteArrowRender.clear();
    for(auto [start, target] : noteList) {
        Point start2D = Point(start / 8, start % 8);
        Point target2D = Point(target / 8, target % 8);
        Point printPosStart, printPosTarget;
        printPosStart.x = boardPosition.x + cellSize.x * start2D.y;
        printPosStart.y = boardPosition.y + cellSize.y * (7 - start2D.x);

        printPosTarget.x = boardPosition.x + cellSize.x * target2D.y;
        printPosTarget.y = boardPosition.y + cellSize.y * (7 - target2D.x);

        if (start == target) {
            noteCircleRender.push_back(Circle(printPosStart));
        }
        else {
            noteArrowRender.emplace_back(Arrow(printPosStart + cellSize / 2, printPosTarget + cellSize / 2, 3, theme->getColorDefault()));
        }
    }

    if (mIsShowSolution && !isEndQuiz()) {
        Move move = movesSolution[cntMoves];
        if (isBoardRotate()) {
            move.startSquare = 63 - move.startSquare;
            move.targetSquare = 63 - move.targetSquare;
        }
        Point start2D = Point(move.startSquare / 8, move.startSquare % 8);
        Point target2D = Point(move.targetSquare / 8, move.targetSquare % 8);
        Point printPosStart, printPosTarget;
        printPosStart.x = boardPosition.x + cellSize.x * start2D.y;
        printPosStart.y = boardPosition.y + cellSize.y * (7 - start2D.x);

        printPosTarget.x = boardPosition.x + cellSize.x * target2D.y;
        printPosTarget.y = boardPosition.y + cellSize.y * (7 - target2D.x);
        noteArrowRender.emplace_back(Arrow(printPosStart + cellSize / 2, printPosTarget + cellSize / 2, 3, theme->getColorDefault()));
    }

    boardPrint->update();
}

void BoardPuzzlesManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*boardPrint, this->state);
    std::vector<std::pair<int, int>> piecePriority;
    for(int i = 0; i < 64; i++)
        piecePriority.emplace_back(piecePrintList[i]->getPriorityPrint(), i);
    std::sort(piecePriority.begin(), piecePriority.end());
    for(std::pair<int, int> data : piecePriority) {
        piecePrintList[data.second]->draw(target);
    }
    for(auto circle : noteCircleRender) {
        target.draw(circle, this->state);
    }
    for(auto arrow : noteArrowRender) {
        target.draw(arrow, this->state);
    }
    target.draw(*promotionManager);
}