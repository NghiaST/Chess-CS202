#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <functional>
#include <bits.h>

Board::Board() {
    if (!shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment)) {
        std::cout << "Error loading shader" << std::endl;
    }
    state.shader = &shader;
    theme = new Theme();
    boardPosition = Point(20, 20);
    boardSize = Point(60, 60) * 8;
    cellSize = boardSize / 8;

    piecePrintList.assign(64, nullptr);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        *it = new Piece(std::distance(piecePrintList.begin(), it), PIECE::NONE);
    }
    boardPrint = new BoardPrint(boardPosition, boardSize);
    gameStatus = GAMESTATUS::NEWGAME;
    turn = CHESS::WHITE;
    winner = CHESS::NONE;

    history = new ChessHistory();
    dataPieceList.assign(64, PIECE::NONE);

    // setup render
    boardPrint->setRenderPosition(boardPosition);
    boardPrint->setRenderSize(boardSize);
    for(int index = 0; index < 64; index++) {
        piecePrintList[index]->setRenderPosition(boardPosition);
        piecePrintList[index]->setRenderSize(cellSize);
    }

    NewGame();
}

Board::Board(Point renderPosition, Point renderSize, Theme* theme) {
    if (!shader.loadFromFile("dat/shader.frag", sf::Shader::Fragment)) {
        std::cout << "Error loading shader" << std::endl;
    }
    state.shader = &shader;
    this->theme = theme;
    this->boardPosition = renderPosition;
    this->boardSize = renderSize;
    cellSize = boardSize / 8;

    piecePrintList.assign(64, nullptr);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        *it = new Piece(std::distance(piecePrintList.begin(), it), PIECE::NONE);
    }
    boardPrint = new BoardPrint(boardPosition, boardSize);
    gameStatus = GAMESTATUS::NEWGAME;
    turn = CHESS::WHITE;
    winner = CHESS::NONE;

    history = new ChessHistory();
    dataPieceList.assign(64, PIECE::NONE);

    // setup render
    boardPrint->setRenderPosition(boardPosition);
    boardPrint->setRenderSize(boardSize);
    for(int index = 0; index < 64; index++) {
        piecePrintList[index]->setRenderPosition(boardPosition);
        piecePrintList[index]->setRenderSize(cellSize);
    }

    NewGame();
}

Board::~Board() {
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        delete *it;
    }
}

// Accessors
int Board::getGameStatus() const {
    return gameStatus;
}
CHESS::COLOR Board::getTurn() const {
    return turn;
}
CHESS::COLOR Board::getWinner() const {
    return winner;
}
std::vector<int> Board::getAllPieceData() const {
    return this->dataPieceList;
}
std::string Board::getStringLastMove() const {
    return history->getStringLastMove();
}
std::string Board::getStringHistory() const {
    return history->getStringHistory();
}


const Piece* Board::getPiece(int squareIndex) const {
    return piecePrintList[squareIndex];
}
const Piece* Board::getPiece(int rank, int file) const {
    return getPiece(rank * 8 + file);
}

const ChessHistory* Board::getHistory() const {
    return history;
}

int Board::getPieceData(int squareIndex) const {
    return dataPieceList[squareIndex];
}

int Board::getPieceColor(int squareIndex) const {
    return dataPieceList[squareIndex] & CHESS::BLACKWHITE;
}

int Board::getPieceType(int squareIndex) const {
    return dataPieceList[squareIndex] & PIECE::ALLTYPE;
}

bool Board::ifCellAttacked(int squareIndex, int myTurn) const {
    for(int otherIndex = 0; otherIndex < 64; otherIndex++) {
        if ((dataPieceList[otherIndex] & myTurn) && ifControll(otherIndex, squareIndex)) {
            return true;
        }
    }
    return false;
}

bool Board::ifControll(int startSquareIndex, int endSquareIndex) const {
    int pieceType = dataPieceList[startSquareIndex] & PIECE::ALLTYPE;
    int pieceColor = dataPieceList[startSquareIndex] & CHESS::BLACKWHITE;
    int curPieceColor = dataPieceList[endSquareIndex] & CHESS::BLACKWHITE;
    Point startIndex2D(startSquareIndex / 8, startSquareIndex % 8);
    Point endIndex2D(endSquareIndex / 8, endSquareIndex % 8);
    Point diff = endIndex2D - startIndex2D;
    int direct = (pieceColor == CHESS::WHITE) ? 1 : -1;

    if (pieceType == PIECE::PAWN) {
        if (curPieceColor == pieceColor) {
            return ILLEGAL;
        }
        else {
            if (abs(diff.y) == 1 && direct * diff.x == 1) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
    }
    else if (pieceType == PIECE::KING) {
        if (curPieceColor == pieceColor) {
            return ILLEGAL;
        }
        else {
            int distance = std::max(abs(diff.x), abs(diff.y));
            if (distance == 1) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
    }
    else {
        return ifMoveLegalWithoutCheck(startSquareIndex, endSquareIndex);
    }
}

int Board::ifMoveLegalWithoutCheck(int startSquareIndex, int endSquareIndex) const {
    return ifMoveLegalWithoutCheck(startSquareIndex, endSquareIndex, dataPieceList);
}
int Board::ifMoveLegalWithoutCheck(int startSquareIndex, int endSquareIndex, std::vector<int> tmpDataPieceList) const
{
    std::function<int(int)> getPieceType = [&](int squareIndex) {
        return tmpDataPieceList[squareIndex] & PIECE::ALLTYPE;
    };
    std::function<int(int)> getPieceColor = [&](int squareIndex) {
        return tmpDataPieceList[squareIndex] & CHESS::BLACKWHITE;
    };

    if (endSquareIndex < 0 || endSquareIndex > 63 || startSquareIndex == endSquareIndex) {
        return ILLEGAL;
    }

    Point startIndex2D(startSquareIndex / 8, startSquareIndex % 8);
    Point endIndex2D(endSquareIndex / 8, endSquareIndex % 8);
    Point diff = endIndex2D - startIndex2D;
    int pieceType = getPieceType(startSquareIndex);
    int pieceColor = getPieceColor(startSquareIndex);
    int playerRank = (pieceColor == CHESS::WHITE ? startIndex2D.x : 7 - startIndex2D.x);

    if (pieceType == PIECE::NONE) {
        return ILLEGAL;
    }
    else if (getPieceColor(startSquareIndex) == getPieceColor(endSquareIndex)) {
        return ILLEGAL;
    }
    if (pieceType == PIECE::KING) {
        int distance = std::max(abs(diff.x), abs(diff.y));
        if (distance == 1) {
            return LEGAL;
        }
        else if (abs(diff.y) == 2 && diff.x == 0) {
            if (playerRank == 0 && startIndex2D.y == 4) {
                int color = (pieceColor == CHESS::WHITE ? 0 : 1);
                int side = (endIndex2D.y == 2 ? 0 : 1);
                bool isCastle = history->isCastlePossible(color, side);
                if (isCastle) {
                    int rookFile = side * 7;
                    int stepFile = (side == 0 ? -1 : 1);
                    int newdiffFile = abs(rookFile - startIndex2D.y);
                    for(int i = 1; i < newdiffFile; i++) {
                        if (getPieceType(startIndex2D.x * 8 + (startIndex2D.y + i * stepFile)) != PIECE::NONE) {
                            return ILLEGAL;
                        }
                    }
                    return CASTLE;
                }
                else {
                    return ILLEGAL;
                }
            }
            else {
                return ILLEGAL;
            }
        }
        else {
            return ILLEGAL;
        }
    }
    if (pieceType == PIECE::QUEEN) {
        // implementation of ifMoveLegal function for queen
        if (diff.x != 0 && diff.y != 0 && abs(diff.x) != abs(diff.y)) {
            return ILLEGAL;
        }
        else {
            int stepRank = (diff.x >= 0 ? diff.x > 0 ? 1 : 0 : -1);
            int stepFile = (diff.y >= 0 ? diff.y > 0 ? 1 : 0 : -1);
            int totaldiff = (int)abs(diff.x) | (int)abs(diff.y);
            for (int i = 1; i < totaldiff; i++) {
                if (getPieceType((startIndex2D.x + i * stepRank) * 8 + (startIndex2D.y + i * stepFile)) != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }
    }
    if (pieceType == PIECE::BISHOP) {
        // implementation of ifMoveLegal function for bishop
        if (diff.x == 0 || diff.y == 0 || abs(diff.x) != abs(diff.y)) {
            return ILLEGAL;
        }
        else {
            int stepRank = diff.x / abs(diff.x);
            int stepFile = diff.y / abs(diff.y);
            for (int i = 1; i < abs(diff.y); i++) {
                if (getPieceType((startIndex2D.x + i * stepRank) * 8 + (startIndex2D.y + i * stepFile)) != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }

    }
    if (pieceType == PIECE::KNIGHT) {
        // implementation of ifMoveLegal function for knight
        if (abs(diff.x) == 1 && abs(diff.y) == 2) {
            return LEGAL;
        }
        else if (abs(diff.x) == 2 && abs(diff.y) == 1) {
            return LEGAL;
        }
        else {
            return ILLEGAL;
        }
    }
    if (pieceType == PIECE::ROOK) {
        // implementation of ifMoveLegal function for rook
        if (diff.x != 0 && diff.y != 0) {
            return ILLEGAL;
        }
        else {
            int stepRank = (diff.x >= 0 ? diff.x > 0 ? 1 : 0 : -1);
            int stepFile = (diff.y >= 0 ? diff.y > 0 ? 1 : 0 : -1);
            for (int i = 1; i < abs(diff.x + diff.y); i++) {
                if (getPieceType((startIndex2D.x + i * stepRank) * 8 + (startIndex2D.y + i * stepFile)) != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }
    }
    if (pieceType == PIECE::PAWN) {
        // implementation of ifMoveLegal function for pawn
        int direct = (pieceColor == CHESS::WHITE) ? 1 : -1;
        if (diff.y == 0 && direct * diff.x == 1) {
            if (getPieceType(endSquareIndex) == PIECE::NONE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
        else if (abs(diff.y) == 1 && direct * diff.x == 1) {
            int curPieceColor = getPieceColor(endSquareIndex);
            if ((curPieceColor ^ pieceColor) == CHESS::BLACKWHITE) {
                return LEGAL;
            }
            else if (curPieceColor == CHESS::NONE) {
                // check if enpassant
                if (playerRank != 4) {
                    return ILLEGAL;
                }
                int indexEnpassant = endSquareIndex - direct;
                int preIndexEnpassant = endSquareIndex + direct;
                const MovingStore lastMove = history->getLastMove();
                if (lastMove.preIndex == preIndexEnpassant && lastMove.curIndex == indexEnpassant && (lastMove.preData & PIECE::PAWN)) {
                    return ENPASSANT;
                }
                else {
                    return ILLEGAL;
                }
            }
            else {
                return ILLEGAL;
            }
        }
        else if (diff.y == 0 && direct * diff.x == 2) {
            if (playerRank < 2 && getPieceType(endSquareIndex) == PIECE::NONE && getPieceType((startIndex2D.x + direct) * 8 + startIndex2D.y) == PIECE::NONE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
    }
    return ILLEGAL;
}

int Board::ifMoveLegal(int startSquareIndex, int endSquareIndex) const {
    int status = ifMoveLegalWithoutCheck(startSquareIndex, endSquareIndex);
    if (status == ILLEGAL) return status;
    if (status == CASTLE) {
        int direct = endSquareIndex < startSquareIndex ? -1 : 1;
        for(int i = 0; i < 3; i++) {
            int tmpSquareIndex = startSquareIndex + direct * i;
            if (ifCellAttacked(tmpSquareIndex, turn ^ CHESS::BOTHCOLOR)) {
                return ILLEGAL;
            }
        }
    }

    std::vector<int> newDataPieceList = dataPieceList;
    newDataPieceList[endSquareIndex] = newDataPieceList[startSquareIndex];
    newDataPieceList[startSquareIndex] = PIECE::NONE;
    if (status == ENPASSANT) {
        int direct = dataPieceList[startSquareIndex] & CHESS::WHITE ? 8 : -8;
        newDataPieceList[endSquareIndex - direct] = PIECE::NONE;
    }
    if (status == CASTLE) {
        int rookFile = (endSquareIndex < startSquareIndex ? 0 : 7);
        int rookRank = startSquareIndex % 8;
        int rookEndFile = (endSquareIndex < startSquareIndex ? 3 : 5);
        newDataPieceList[rookRank * 8 + rookEndFile] = newDataPieceList[rookRank * 8 + rookFile];
        newDataPieceList[rookRank * 8 + rookFile] = PIECE::NONE;
    }

    int kingPos = -1;
    for(int i = 0; i < 64; i++) {
        if (newDataPieceList[i] == (PIECE::KING + turn)) {
            kingPos = i;
            break;
        }
    }
    for(int i = 0; i < 64; i++) {
        if (ifMoveLegalWithoutCheck(i, kingPos, newDataPieceList) != ILLEGAL) {
            return ILLEGAL;
        }
    }
    return status;
}

int Board::ifMoveLegal(int startRank, int startFile, int endRank, int endFile) const {
    return ifMoveLegal(startRank * 8 + startFile, endRank * 8 + endFile);
}

std::vector<int> Board::getPossibleMove(int startSquareIndex) const
{
    std::vector<int> legalMove;
    for (int i = 0; i < 64; i++) {
        if (ifMoveLegal(startSquareIndex, i) != ILLEGAL) {
            legalMove.push_back(i);
        }
    }
    return legalMove;
}

std::vector<Point> Board::getAllPossibleMove() const
{
    std::vector<Point> legalMove;
    for(int i = 0; i < 64; i++) 
    if (dataPieceList[i] & turn) {
        for (int j = 0; j < 64; j++) {
            if (ifMoveLegal(i, j)) {
                legalMove.push_back(Point(i, j));
            }
        }
    }
    return legalMove;
}

int Board::getKingSquareIndex() const {
    for(int i = 0; i < 64; i++) {
        if (dataPieceList[i] == (PIECE::KING + turn)) {
            return i;
        }
    }
    return -1;
}

bool Board::ifCheck() const {
    int kingPos = -1;
    for(int i = 0; i < 64; i++) {
        if (dataPieceList[i] == (PIECE::KING + turn)) {
            kingPos = i;
            break;
        }
    }
    return ifCellAttacked(kingPos, turn ^ CHESS::BOTHCOLOR);
}

bool Board::ifCheckMate() const {
    return ifCheck() && getAllPossibleMove().size() == 0;
}

bool Board::ifStaleMate() const {
    return !ifCheck() && getAllPossibleMove().size() == 0;
}

int Board::TryMove(int startSquareIndex, int endSquareIndex) {
    int status = ifMoveLegalWithoutCheck(startSquareIndex, endSquareIndex);
    history->addMove(MovingStore(startSquareIndex, endSquareIndex, piecePrintList[startSquareIndex]->getPieceData(), piecePrintList[endSquareIndex]->getPieceData(), status));

    dataPieceList[endSquareIndex] = dataPieceList[startSquareIndex];
    dataPieceList[startSquareIndex] = PIECE::NONE;
    if (status == ENPASSANT) {
        int direct = dataPieceList[startSquareIndex] & CHESS::WHITE ? 8 : -8;
        dataPieceList[endSquareIndex - direct] = PIECE::NONE;
    }
    if (status == CASTLE) {
        int rookRank = startSquareIndex / 8;
        int rookFile = (endSquareIndex < startSquareIndex ? 0 : 7);
        int rookEndFile = (endSquareIndex < startSquareIndex ? 3 : 5);
        dataPieceList[rookRank * 8 + rookEndFile] = dataPieceList[rookRank * 8 + rookFile];
        dataPieceList[rookRank * 8 + rookFile] = PIECE::NONE;
    }
    turn = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    return status;
}

bool Board::MakeMove(int startSquareIndex, int endSquareIndex) {
    if (dataPieceList[startSquareIndex] & turn != turn) return false;
    int status = ifMoveLegal(startSquareIndex, endSquareIndex);
    if (status == ILLEGAL) return false;
    printf("Make move: %d %d\n", startSquareIndex, endSquareIndex);
    history->addMove(MovingStore(startSquareIndex, endSquareIndex, piecePrintList[startSquareIndex]->getPieceData(), piecePrintList[endSquareIndex]->getPieceData(), status));

    dataPieceList[endSquareIndex] = dataPieceList[startSquareIndex];
    dataPieceList[startSquareIndex] = PIECE::NONE;
    if (status == ENPASSANT) {
        int direct = dataPieceList[startSquareIndex] & CHESS::WHITE ? 8 : -8;
        dataPieceList[endSquareIndex - direct] = PIECE::NONE;
    }
    if (status == CASTLE) {
        int rookRank = startSquareIndex / 8;
        int rookFile = (endSquareIndex < startSquareIndex ? 0 : 7);
        int rookEndFile = (endSquareIndex < startSquareIndex ? 3 : 5);
        dataPieceList[rookRank * 8 + rookEndFile] = dataPieceList[rookRank * 8 + rookFile];
        dataPieceList[rookRank * 8 + rookFile] = PIECE::NONE;
    }

    turn = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    isPieceSelected = false;
    isPieceHold = false;
    preSquareIndex = startSquareIndex;
    curSquareIndex = endSquareIndex;
    gameStatus = ONGOING;
    if (ifCheckMate()) {
        gameStatus = ENDGAME;
        winner = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    }
    else if (ifStaleMate()) {
        gameStatus = ENDGAME;
        winner = CHESS::NONE;
    }

    return true;
}

bool Board::UndoMove() {
    if (!history->getCntMove()) return false;
    MovingStore lastMove = history->getLastMove();
    dataPieceList[lastMove.preIndex] = lastMove.preData;
    dataPieceList[lastMove.curIndex] = lastMove.curData;
    if (lastMove.moveStatus == ENPASSANT) {
        int direct = dataPieceList[lastMove.preIndex] & CHESS::WHITE ? 8 : -8;
        dataPieceList[lastMove.curIndex - direct] = lastMove.curData;
    }
    if (lastMove.moveStatus == CASTLE) {
        int rookRank = lastMove.preIndex / 8;
        int rookFile = (lastMove.curIndex < lastMove.preIndex ? 0 : 7);
        int rookEndFile = (lastMove.curIndex < lastMove.preIndex ? 3 : 5);
        dataPieceList[rookRank * 8 + rookFile] = dataPieceList[rookRank * 8 + rookEndFile];
        dataPieceList[rookRank * 8 + rookEndFile] = PIECE::NONE;
    }
    turn = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    history->popMove();
    gameStatus = ONGOING;
    return true;
}

void Board::NewGame() {
    dataPieceList = std::vector<int>(64, PIECE::NONE);
    dataPieceList[0]  = dataPieceList[7] = PIECE::ROOK + CHESS::WHITE;
    dataPieceList[1]  = dataPieceList[6] = PIECE::KNIGHT + CHESS::WHITE;
    dataPieceList[2] = dataPieceList[5] = PIECE::BISHOP + CHESS::WHITE;
    dataPieceList[3] = PIECE::QUEEN + CHESS::WHITE;
    dataPieceList[4] = PIECE::KING + CHESS::WHITE;
    dataPieceList[56]  = dataPieceList[63] = PIECE::ROOK + CHESS::BLACK;
    dataPieceList[57] = dataPieceList[62] = PIECE::KNIGHT + CHESS::BLACK;
    dataPieceList[58] = dataPieceList[61] = PIECE::BISHOP + CHESS::BLACK;
    dataPieceList[59] = PIECE::QUEEN + CHESS::BLACK;
    dataPieceList[60] = PIECE::KING + CHESS::BLACK;
    for(int i = 0; i < 8; i++) {
        dataPieceList[i + 8] = PIECE::PAWN + CHESS::WHITE;
        dataPieceList[i + 48] = PIECE::PAWN + CHESS::BLACK;
    }

    // setup piece
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->setPieceData(dataPieceList[i]);
    }

    // setup game status
    gameStatus = GAMESTATUS::NEWGAME;
    turn = CHESS::WHITE;
    winner = CHESS::NONE;

    // setup other
    isPieceSelected = false;
    isPieceHold = false;
    selectedPieceIndex = -1;
    preSquareIndex = -1;
    curSquareIndex = -1;
    history->clear();
    mousePosition = Point(0, 0);
}

std::string Board::handleEvent(const sf::Event& event) {
    std::string res = "";
    if (event.type == sf::Event::MouseMoved) {
        mousePosition = Point(event.mouseMove.x, event.mouseMove.y);
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        mousePosition = Point(event.mouseButton.x, event.mouseButton.y);
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (gameStatus == NEWGAME || gameStatus == ONGOING) {
                if (boardPrint->isMouseOn(mousePosition)) {
                    printf("HandleEvent: %f %f\n", mousePosition.x, mousePosition.y);
                    noteViewIndexList.clear();
                    sf::Vector2i coordChess;
                    coordChess.x = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    coordChess.y = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    int squareIndex = coordChess.x * 8 + coordChess.y;
                    if (!isPieceSelected) {
                        if (getPieceColor(squareIndex) == turn) {
                            isPieceSelected = true;
                            isPieceHold = true;
                            selectedPieceIndex = squareIndex;
                            holdPieceIndex = squareIndex;
                            possibleIndexList = getPossibleMove(squareIndex);
                        }
                    }
                    else {
                        if (selectedPieceIndex == squareIndex) {
                            isPieceSelected = false;
                            isPieceHold = true;
                        }
                        else /// when click other pos
                        if (MakeMove(selectedPieceIndex, squareIndex)) {
                            res = "make move";
                        }
                        else if (getPieceColor(squareIndex) == turn) {
                            isPieceSelected = true;
                            isPieceHold = true;
                            selectedPieceIndex = squareIndex;
                            holdPieceIndex = squareIndex;
                            possibleIndexList = getPossibleMove(squareIndex);
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
                        if (MakeMove(selectedPieceIndex, squareIndex)) {
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

    
    if (gameStatus != ENDGAME && turn == CHESS::BLACK) {
        std::vector<Point> possibleMoveList = getAllPossibleMove();
        if (possibleMoveList.size() == 0) {
            printf("End game\n");
        }
        else {
            Point id = possibleMoveList[rand() % possibleMoveList.size()];
            MakeMove(id.x, id.y);
            isPieceSelected = false;
            isPieceHold = false;
            selectedPieceIndex = -1;
            preSquareIndex = id.x;
            curSquareIndex = id.y;
        }
    }
    // if (gameStatus != ENDGAME && turn == CHESS::WHITE) {
    //     std::vector<Point> possibleMoveList = getAllPossibleMove();
    //     Point id = possibleMoveList[rand() % possibleMoveList.size()];
    //     if (!MakeMove(id.x, id.y)) {
    //         printf("End game\n");
    //     }
    //     else {
    //         isPieceSelected = false;
    //         isPieceHold = false;
    //         selectedPieceIndex = -1;
    //         preSquareIndex = id.x;
    //         curSquareIndex = id.y;
    //     }
    // }
    // sf::sleep(sf::milliseconds(100));


    return res;
}

std::string Board::update(sf::Time deltaTime) {
    std::string res = "";
    /// logic (time)
    /*
        code something here
    */
    return res;
}

void Board::updateRender() {

    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->setPieceData(dataPieceList[i]);
        piecePrintList[i]->setMouseStatus(MOUSE::NONE);
        boardPrint->setStateCell(i, BoardPrint::COMMON);
    }
    if (ifCheck()) {
        boardPrint->setStateCell(getKingSquareIndex(), BoardPrint::CHECK);
    }
    if (ifCheckMate()) {
        boardPrint->setStateCell(getKingSquareIndex(), BoardPrint::CHECKMATE);
    }
    if (history->getCntMove()) {
        MovingStore lastMove = history->getLastMove();
        boardPrint->setStateCell(lastMove.preIndex, BoardPrint::PREMOVE);
        boardPrint->setStateCell(lastMove.curIndex, BoardPrint::PREMOVE);
    }
    if (isPieceSelected | isPieceHold) {
        boardPrint->setStateCell(selectedPieceIndex, BoardPrint::SELECTED);
        for(int u : possibleIndexList) 
            boardPrint->setStateCell(u, BoardPrint::POSSIBLE);
    }
    if (isPieceHold) {
        boardPrint->setStateCell(holdPieceIndex, BoardPrint::SELECTED);
        piecePrintList[holdPieceIndex]->setMouseStatus(MOUSE::HOLD, mousePosition);
    }

    boardPrint->update(theme);
    for(int i = 0; i < 64; i++) {
        piecePrintList[i]->update(theme);
    }
    
}

void Board::render(sf::RenderTarget& target, sf::RenderStates state) const
{
    state = this->state;
    boardPrint->render(target, state);
    std::vector<std::pair<int, int>> piecePriority;
    for(int i = 0; i < 64; i++)
        piecePriority.emplace_back(piecePrintList[i]->getPriorityPrint(), i);
    std::sort(piecePriority.begin(), piecePriority.end());
    for(std::pair<int, int> data : piecePriority) {
        piecePrintList[data.second]->render(target, state);
    }
}