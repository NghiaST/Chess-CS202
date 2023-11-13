#include "BoardManager.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <functional>
#include <bits.h>

BoardManager::BoardManager(Point renderPosition, Point renderSize, Theme* theme) {
    board = new NewBoard();
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
        *it = new Piece(std::distance(piecePrintList.begin(), it), PIECE::None);
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

const NewBoard &BoardManager::getBoard() const {
    return *board;
}

// Modifiers

void BoardManager::freshState() {
    isCheck = board->ifCheck();
    isCheckMate = board->ifCheckMate();
    isStaleMate = board->ifStaleMate();
    isWhiteTurn = board->ifWhiteTurn();
    isBotRunning = false;

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

void BoardManager::NewGame() {
    board->LoadBasicPosition();
    isBot[0] = true;
    isBot[1] = false;
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

bool BoardManager::ManagerMove(int startSquare, int targetSquare) {
    std::vector<Move> moveList = board->getLegalMoveAt(startSquare);
    bool ret = false;
    for(Move move : moveList) {
        if (move.targetSquare == targetSquare) {
            board->MakeMove(move);
            isPieceSelected = false;
            isPieceHold = false;
            preSquareIndex = move.startSquare;
            curSquareIndex = move.targetSquare;
            movesUndoList.clear();
            freshState();
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
    std::string res = "";
    if (event.type == sf::Event::MouseMoved) {
        mousePosition = Point(event.mouseMove.x, event.mouseMove.y);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        mousePosition = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (gameStatus == NEWGAME || gameStatus == ONGOING) {
                if (boardPrint->isMouseOn(mousePosition)) {
                    noteViewIndexList.clear();
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
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
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (gameStatus == NEWGAME || gameStatus == ONGOING) {
                if (boardPrint->isMouseOn(mousePosition)) {
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
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
    }
    // if (gameStatus != ENDGAME && isWhiteTurn == false) {
    //     std::vector<Move> legalMoveList = NewBoard::getLegalMoveList();
    //     if (legalMoveList.size() == 0) {
    //         printf("End game\n");
    //     }
    //     else {
    //         Move move = legalMoveList[rand() % legalMoveList.size()];
    //         ManagerMove(move.startSquare, move.targetSquare);
    //     }
    // }
    // sf::sleep(sf::milliseconds(100));

    return res;
}

std::string BoardManager::update(sf::Time deltaTime) {
    std::string res = "";
    if (gameStatus != ENDGAME && isBot[isWhiteTurn]) {
        if (!isBotRunning) {
            isBotRunning = true;
            bot->LoadBoard(*board);
        }
        bot->Thinking();
        if (bot->ifThinkingDone()) {
            Move move = bot->getBestMove();
            ManagerMove(move.startSquare, move.targetSquare);
            isBotRunning = false;
            res = "make move";
        }
    }
    /// logic (time)
    /*
        code something here
    */
    return res;
}

void BoardManager::updateRender() {
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->setPiece(board->getPiece(i));
        piecePrintList[i]->setMouseStatus(MOUSE::NONE);
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
        piecePrintList[holdPieceIndex]->setMouseStatus(MOUSE::HOLD, mousePosition);
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
}