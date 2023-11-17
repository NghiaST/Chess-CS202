#include "BoardManager.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <functional>
#include <bits.h>

BoardManager::BoardManager(Point renderPosition, Point renderSize, Theme* theme) {
    board = new Board();
    bot = new Bot();
    if (!shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment)) {
        printf("Error loading shader\n");
    }
    state.shader = &shader;
    this->theme = theme;
    this->boardPosition = renderPosition;
    this->boardSize = renderSize;
    cellSize = boardSize / 8;

    piecePrintList.assign(64, nullptr);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        *it = new PiecePrint(std::distance(piecePrintList.begin(), it), PIECE::None);
    }
    boardPrint = new BoardPrint(boardPosition, boardSize, &theme->getTextureBoard());
    gameStatus = GAMESTATUS::NEWGAME;
    gameResult = CHESS::None;

    // setup render
    for(int index = 0; index < 64; index++) {
        piecePrintList[index]->setRenderPosition(boardPosition);
        piecePrintList[index]->setRenderSize(cellSize);
    }

    NewGame();
}

BoardManager::~BoardManager() {
    delete board;
    delete bot;
    delete boardPrint;
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        delete *it;
    }
}

bool BoardManager::ifBoardRotate() const {
    return isBoardRotate;
}

// Accessors
int BoardManager::getGameStatus() const {
    return gameStatus;
}
CHESS::COLOR BoardManager::getTurn() const {
    return CHESS::COLOR(isWhiteTurn);
}
int BoardManager::getResult() const {
    return gameResult;
}

bool BoardManager::ifBotTurn() const {
    return isBot[isWhiteTurn];
}

bool BoardManager::ifCheckMate() const {
    return isCheckMate;
}

bool BoardManager::ifStaleMate() const {
    return isStaleMate;
}

bool BoardManager::ifEndGame() const {
    return gameStatus == ENDGAME;
}

const Board &BoardManager::getBoard() const {
    return *board;
}

// Modifiers

void BoardManager::freshState() {
    isCheck = board->ifCheck();
    isCheckMate = board->ifCheckMate();
    isStaleMate = board->ifStaleMate();
    isWhiteTurn = board->ifWhiteTurn();
    isBotRunning = false;
    isEvent = true;
    isNoteHold = false;
    noteList.clear();
    suggestMoves.clear();

    if (isCheckMate) {
        gameStatus = ENDGAME;
        gameResult = (CHESS::COLOR) (isWhiteTurn ^ 1);
    }
    else if (isStaleMate) {
        gameStatus = ENDGAME;
        gameResult = CHESS::COLOR::Both;
    }
    else if (gameStatus == NEWGAME) {}
    else {
        gameStatus = ONGOING;
    }
}

void BoardManager::setBoardRotate(bool isBoardRotate) {
    this->isBoardRotate = isBoardRotate;
    boardPrint->setBoardRotate(isBoardRotate);
    for(int i = 0; i < 64; i++) {
        int index = isBoardRotate ? 63 - i : i;
        piecePrintList[i]->setIndex(index);
    }
}

void BoardManager::NewGame() {
    board->LoadBasicPosition();
    mode = FileInit::LoadMode();
    FileInit::LoadOptions(mode, level, isBotHelp);
    if (mode == 0) {
        isBot = {true, false};
    }
    else if (mode == 1) {
        isBot = {false, true};
    }
    else if (mode == 2) {
        isBot = {false, false};
    }
    else if (mode == 3) {
        isBot = {true, true};
    }
    else {
        isBot = {false, false};
    }

    setBoardRotate(mode == 1);
    gameStatus = GAMESTATUS::NEWGAME;
    gameResult = CHESS::None;
    isPieceSelected = false;
    isPieceHold = false;
    selectedPieceIndex = -1;
    preSquareIndex = -1;
    curSquareIndex = -1;
    freshState();
}

void BoardManager::Undo() {
    printf("UNDO\n");
    if (board->isHistoryEmpty()) return;
    movesUndoList.push_back(board->getLastMove());
    board->UndoMove();
    freshState();

    if (isBot[isWhiteTurn] == false) return;
    if (board->isHistoryEmpty()) return;
    movesUndoList.push_back(board->getLastMove());
    board->UndoMove();
    freshState();
}

void BoardManager::Redo() {
    printf("REDO\n");
    if (movesUndoList.size() == 0) return;
    board->MakeMove(movesUndoList.back());
    movesUndoList.pop_back();
    freshState();

    if (movesUndoList.size() == 0) return;
    if (isBot[isWhiteTurn] == false) return;
    board->MakeMove(movesUndoList.back());
    movesUndoList.pop_back();
    freshState();
}

void BoardManager::setBotHelp(bool isBotHelp) {
    this->isBotHelp = isBotHelp;
    suggestMoves.clear();
    isEvent = true;
}

#include "../Helpers/MoveUtility.hpp"
bool BoardManager::ManagerMove(int startSquare, int targetSquare, bool isBotMove) {
    if (!isBotMove && isBot[isWhiteTurn]) return false;
    std::vector<Move> moveList = board->getLegalMoveAt(startSquare);
    for(Move move : moveList) {
        if (move.targetSquare == targetSquare) {
            std::string SANname = MoveUtility::GetMoveNameSAN(move, *board);
            std::cout << SANname << std::endl;
            Move tmp2 = MoveUtility::GetMoveFromSAN(SANname, *board);
            std::cout << tmp2.startSquare << " " << tmp2.targetSquare << std::endl;
            
            board->MakeMove(move);
            isPieceSelected = false;
            isPieceHold = false;
            preSquareIndex = move.startSquare;
            curSquareIndex = move.targetSquare;
            movesUndoList.clear();
            freshState();
            FileInit::SaveGame(*board, mode, level, 100, 100);
            
            return true;
        }
    }
    return false;
}

std::vector<int> BoardManager::getLegalIndexAt(int squareIndex) {
    std::vector<int> legalIndexs;
    std::vector<Move> legalMoves = board->getLegalMoveAt(squareIndex);
    for(Move move : legalMoves)
        legalIndexs.push_back(move.targetSquare);
    return legalIndexs;
}

std::string BoardManager::handleEvent(const sf::Event& event) {
    isEvent = true;
    std::string res = "";
    if (event.type == sf::Event::MouseMoved) {
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
    if (event.type == sf::Event::MouseButtonPressed) {
        mousePosition = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (boardPrint->isMouseOn(mousePosition)) {
                noteList.clear();
                isNoteHold = false;
                if (gameStatus == NEWGAME || gameStatus == ONGOING) {
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    if (isBoardRotate) {
                        coordChess.x = 7 - coordChess.x;
                        coordChess.y = 7 - coordChess.y;
                    }
                    int squareIndex = coordChess.x * 8 + coordChess.y;
                    if (!isPieceSelected) {
                        if (PIECE::isPieceYourTurn(board->getPiece(squareIndex), isWhiteTurn)) {
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
                        else /// when click other pos
                        if (ManagerMove(selectedPieceIndex, squareIndex)) {
                            res = "make move";
                        }
                        else if (PIECE::PieceColor(board->getPiece(squareIndex)) == PIECE::boolToColor(isWhiteTurn)) {
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
            if (gameStatus == NEWGAME || gameStatus == ONGOING) {
                if (boardPrint->isMouseOn(mousePosition)) {
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    if (isBoardRotate) {
                        coordChess.x = 7 - coordChess.x;
                        coordChess.y = 7 - coordChess.y;
                    }
                    int squareIndex = coordChess.x * 8 + coordChess.y;
                    if (isPieceHold) {
                        isPieceHold = false;
                        if (ManagerMove(selectedPieceIndex, squareIndex)) {
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

std::string BoardManager::update(sf::Time deltaTime) {
    std::string res = "";
    if (gameStatus != ENDGAME) {
        if (isBot[isWhiteTurn]) {
            if (!isBotRunning) {
                isBotRunning = true;
                bot->setTimeThinkingMs(2500);
                bot->LoadBoard(*board);
            }
            bot->Thinking();
            if (bot->ifThinkingDone()) {
                Move move = bot->getBestMove();
                ManagerMove(move.startSquare, move.targetSquare, true);
                isBotRunning = false;
                res = "make move";
            }
        }
        else if (isBotHelp) {
            if (!isBotRunning) {
                isBotRunning = true;
                bot->setTimeThinkingMs(10000);
                bot->LoadBoard(*board);
            }
            bot->Thinking();
            std::vector<Move> newSuggestMoves = bot->getRankMove(5);
            if (newSuggestMoves != suggestMoves) {
                suggestMoves = newSuggestMoves;
                isEvent = true;
            }
        }
    }
    /// logic (time)
    /*
        code something here
    */
    return res;
}

void BoardManager::updateRender() {
    if (!isEvent) return;
    isEvent = false;
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->setPiece(board->getPiece(i));
        piecePrintList[i]->setMouseStatus(MOUSE::None);
        boardPrint->setStateCell(i, BoardPrint::Common);
    }
    if (isCheck) {
        boardPrint->setStateCell(board->getKingSquareIndex(isWhiteTurn), BoardPrint::Check);
    }
    if (isCheckMate) {
        boardPrint->setStateCell(board->getKingSquareIndex(isWhiteTurn), BoardPrint::CheckMate);
    }
    if (isStaleMate) {
        boardPrint->setStateCell(board->getKingSquareIndex(isWhiteTurn), BoardPrint::StaleMate);
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

    for(int i = 0; i < (int) suggestMoves.size(); i++) {
        Move move = suggestMoves[i];
        int start = move.startSquare;
        int target = move.targetSquare;
        if (isBoardRotate) {
            start = 63 - start;
            target = 63 - target;
        }
        Point start2D = Point(start / 8, start % 8);
        Point target2D = Point(target / 8, target % 8);
        Point printPosStart, printPosTarget;
        printPosStart.x = boardPosition.x + cellSize.x * start2D.y;
        printPosStart.y = boardPosition.y + cellSize.y * (7 - start2D.x);

        printPosTarget.x = boardPosition.x + cellSize.x * target2D.y;
        printPosTarget.y = boardPosition.y + cellSize.y * (7 - target2D.x);

        noteArrowRender.emplace_back(Arrow(printPosStart + cellSize / 2, printPosTarget + cellSize / 2, i, theme->getColorDefault()));
    }

    boardPrint->update();
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->update(theme);
    }
}

void BoardManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
}