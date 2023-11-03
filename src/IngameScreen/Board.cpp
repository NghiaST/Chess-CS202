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

    pieceList.assign(64, nullptr);
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
        *it = new Piece(std::distance(pieceList.begin(), it), PIECE::NONE);
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
    for(int i = 0; i < 64; i++) {
        pieceList[i]->setRenderPosition(boardPosition);
        pieceList[i]->setRenderSize(cellSize);
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

    pieceList.assign(64, nullptr);
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
        *it = new Piece(std::distance(pieceList.begin(), it), PIECE::NONE);
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
    for(int i = 0; i < 64; i++) {
        pieceList[i]->setRenderPosition(boardPosition);
        pieceList[i]->setRenderSize(cellSize);
    }

    NewGame();
}

Board::~Board() {
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
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


const Piece* Board::getPiece(int position) const {
    return pieceList[position];
}
const Piece* Board::getPiece(int posx, int posy) const {
    return getPiece(posx * 8 + posy);
}

const ChessHistory* Board::getHistory() const {
    return history;
}

int Board::getPieceData(int position) const {
    return dataPieceList[position];
}

int Board::getPieceColor(int position) const {
    return dataPieceList[position] & CHESS::BLACKWHITE;
}

int Board::getPieceType(int position) const {
    return dataPieceList[position] & PIECE::ALLTYPE;
}

bool Board::ifCellAttacked(int position, int myTurn) const {
    for(int i = 0; i < 64; i++) {
        if ((dataPieceList[i] & myTurn) && ifControll(i, position)) {
            return true;
        }
    }
    return false;
}

bool Board::ifControll(int startpos, int endpos) const {
    int pieceType = dataPieceList[startpos] & PIECE::ALLTYPE;
    int pieceColor = dataPieceList[startpos] & CHESS::BLACKWHITE;
    int curPieceColor = dataPieceList[endpos] & CHESS::BLACKWHITE;
    Point startCoord(startpos / 8, startpos % 8);
    Point endCoord(endpos / 8, endpos % 8);
    Point diff = endCoord - startCoord;
    int direct = (pieceColor == CHESS::WHITE) ? 1 : -1;

    if (pieceType == PIECE::PAWN) {
        if (curPieceColor == pieceColor) {
            return ILLEGAL;
        }
        else {
            if (abs(diff.x) == 1 && direct * diff.y == 1) {
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
        return ifMoveLegalWithoutCheck(startpos, endpos);
    }
}

int Board::ifMoveLegalWithoutCheck(int startpos, int endpos) const {
    return ifMoveLegalWithoutCheck(startpos, endpos, dataPieceList);
}
int Board::ifMoveLegalWithoutCheck(int startpos, int endpos, std::vector<int> tmpDataPieceList) const
{
    std::function<int(int)> getPieceType = [&](int position) {
        return tmpDataPieceList[position] & PIECE::ALLTYPE;
    };
    std::function<int(int)> getPieceColor = [&](int position) {
        return tmpDataPieceList[position] & CHESS::BLACKWHITE;
    };

    if (endpos < 0 || endpos > 63 || startpos == endpos) {
        return ILLEGAL;
    }

    Point startCoord(startpos / 8, startpos % 8);
    Point endCoord(endpos / 8, endpos % 8);
    Point diff = endCoord - startCoord;
    int pieceType = getPieceType(startpos);
    int pieceColor = getPieceColor(startpos);
    int horizontal = (pieceColor == CHESS::WHITE ? startCoord.y : 7 - startCoord.y);

    if (pieceType == PIECE::NONE) {
        return ILLEGAL;
    }
    else if (getPieceColor(startpos) == getPieceColor(endpos)) {
        return ILLEGAL;
    }
    if (pieceType == PIECE::KING) {
        int distance = std::max(abs(diff.x), abs(diff.y));
        if (distance == 1) {
            return LEGAL;
        }
        else if (abs(diff.x) == 2 && diff.y == 0) {
            if (horizontal == 0 && startCoord.x == 4) {
                int color = (pieceColor == CHESS::WHITE ? 0 : 1);
                int side = (endCoord.x == 2 ? 0 : 1);
                bool isCastle = history->isCastlePossible(color, side);
                if (isCastle) {
                    int rookPosx = side * 7;
                    int stepx = (side == 0 ? -1 : 1);
                    int newdiffx = abs(rookPosx - startCoord.x);
                    for(int i = 1; i < newdiffx; i++) {
                        if (getPieceType((startCoord.x + i * stepx) * 8 + startCoord.y) != PIECE::NONE) {
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
            int stepx = (diff.x >= 0 ? diff.x > 0 ? 1 : 0 : -1);
            int stepy = (diff.y >= 0 ? diff.y > 0 ? 1 : 0 : -1);
            int totaldiff = (int)abs(diff.x) | (int)abs(diff.y);
            for (int i = 1; i < totaldiff; i++) {
                if (getPieceType((startCoord.x + i * stepx) * 8 + (startCoord.y + i * stepy)) != PIECE::NONE) {
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
            int stepx = diff.x / abs(diff.x);
            int stepy = diff.y / abs(diff.y);
            for (int i = 1; i < abs(diff.x); i++) {
                if (getPieceType((startCoord.x + i * stepx) * 8 + (startCoord.y + i * stepy)) != PIECE::NONE) {
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
            int stepx = (diff.x >= 0 ? diff.x > 0 ? 1 : 0 : -1);
            int stepy = (diff.y >= 0 ? diff.y > 0 ? 1 : 0 : -1);
            for (int i = 1; i < abs(diff.x + diff.y); i++) {
                if (getPieceType((startCoord.x + i * stepx) * 8 + (startCoord.y + i * stepy)) != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }
    }
    if (pieceType == PIECE::PAWN) {
        // implementation of ifMoveLegal function for pawn
        int direct = (pieceColor == CHESS::WHITE) ? 1 : -1;
        if (diff.x == 0 && direct * diff.y == 1) {
            if (getPieceType(endpos) == PIECE::NONE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
        else if (abs(diff.x) == 1 && direct * diff.y == 1) {
            int curPieceColor = getPieceColor(endpos);
            if ((curPieceColor ^ pieceColor) == CHESS::BLACKWHITE) {
                return LEGAL;
            }
            else if (curPieceColor == CHESS::NONE) {
                // check if enpassant
                if (horizontal != 4) {
                    return ILLEGAL;
                }
                int posEnpassant = endpos - direct;
                int preEnpassant = endpos + direct;
                const MovingStore lastMove = history->getLastMove();
                if (lastMove.prePos == preEnpassant && lastMove.curPos == posEnpassant && (lastMove.preData & PIECE::PAWN)) {
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
        else if (diff.x == 0 && direct * diff.y == 2) {
            if (horizontal < 2 && getPieceType(endpos) == PIECE::NONE && getPieceType((startCoord.x) * 8 + (startCoord.y + direct)) == PIECE::NONE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
    }
    return ILLEGAL;
}

int Board::ifMoveLegal(int startpos, int endpos) const {
    int status = ifMoveLegalWithoutCheck(startpos, endpos);
    if (status == ILLEGAL) return status;
    if (status == CASTLE) {
        int direct = endpos < startpos ? -8 : 8;
        for(int i = 0; i < 3; i++) {
            int curpos = startpos + direct * i;
            if (ifCellAttacked(curpos, turn ^ CHESS::BOTHCOLOR)) {
                return ILLEGAL;
            }
        }
    }

    std::vector<int> newDataPieceList = dataPieceList;
    newDataPieceList[endpos] = newDataPieceList[startpos];
    newDataPieceList[startpos] = PIECE::NONE;
    if (status == ENPASSANT) {
        int direct = dataPieceList[startpos] & CHESS::WHITE ? 1 : -1;
        newDataPieceList[endpos - direct] = PIECE::NONE;
    }
    if (status == CASTLE) {
        int rookPosx = (endpos < startpos ? 0 : 7);
        int rookPosy = startpos % 8;
        int rookEndx = (endpos < startpos ? 3 : 5);
        newDataPieceList[rookEndx * 8 + rookPosy] = newDataPieceList[rookPosx * 8 + rookPosy];
        newDataPieceList[rookPosx * 8 + rookPosy] = PIECE::NONE;
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

int Board::ifMoveLegal(int startx, int starty, int endx, int endy) const {
    return ifMoveLegal(startx * 8 + starty, endx * 8 + endy);
}

std::vector<int> Board::getPossibleMove(int startpos) const
{
    std::vector<int> legalMove;
    for (int i = 0; i < 64; i++) {
        if (ifMoveLegal(startpos, i) != ILLEGAL) {
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

int Board::getKingPosition() const {
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

int Board::TryMove(int startpos, int endpos) {
    int status = ifMoveLegalWithoutCheck(startpos, endpos);
    history->addMove(MovingStore(startpos, endpos, pieceList[startpos]->getPieceData(), pieceList[endpos]->getPieceData(), status));

    dataPieceList[endpos] = dataPieceList[startpos];
    dataPieceList[startpos] = PIECE::NONE;
    if (status == ENPASSANT) {
        int direct = dataPieceList[startpos] & CHESS::WHITE ? 1 : -1;
        dataPieceList[endpos - direct] = PIECE::NONE;
    }
    if (status == CASTLE) {
        int rookPosx = (endpos < startpos ? 0 : 7);
        int rookPosy = startpos % 8;
        int rookEndx = (endpos < startpos ? 3 : 5);
        dataPieceList[rookEndx * 8 + rookPosy] = dataPieceList[rookPosx * 8 + rookPosy];
        dataPieceList[rookPosx * 8 + rookPosy] = PIECE::NONE;
    }
    turn = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    return status;
}

bool Board::MakeMove(int startpos, int endpos) {
    if (dataPieceList[startpos] & turn != turn) return false;
    int status = ifMoveLegal(startpos, endpos);
    if (status == ILLEGAL) return false;
    printf("Make move: %d %d\n", startpos, endpos);
    history->addMove(MovingStore(startpos, endpos, pieceList[startpos]->getPieceData(), pieceList[endpos]->getPieceData(), status));

    dataPieceList[endpos] = dataPieceList[startpos];
    dataPieceList[startpos] = PIECE::NONE;
    if (status == ENPASSANT) {
        int direct = dataPieceList[startpos] & CHESS::WHITE ? 1 : -1;
        dataPieceList[endpos - direct] = PIECE::NONE;
    }
    if (status == CASTLE) {
        int rookPosx = (endpos < startpos ? 0 : 7);
        int rookPosy = startpos % 8;
        int rookEndx = (endpos < startpos ? 3 : 5);
        dataPieceList[rookEndx * 8 + rookPosy] = dataPieceList[rookPosx * 8 + rookPosy];
        dataPieceList[rookPosx * 8 + rookPosy] = PIECE::NONE;
    }
    turn = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    return true;
}

bool Board::UndoMove() {
    if (!history->getCntMove()) return false;
    MovingStore lastMove = history->getLastMove();
    dataPieceList[lastMove.prePos] = lastMove.preData;
    dataPieceList[lastMove.curPos] = lastMove.curData;
    if (lastMove.moveStatus == ENPASSANT) {
        int direct = dataPieceList[lastMove.prePos] & CHESS::WHITE ? 1 : -1;
        dataPieceList[lastMove.curPos - direct] = lastMove.curData;
    }
    if (lastMove.moveStatus == CASTLE) {
        int rookPosx = (lastMove.curPos < lastMove.prePos ? 0 : 7);
        int rookPosy = lastMove.prePos % 8;
        int rookEndx = (lastMove.curPos < lastMove.prePos ? 3 : 5);
        dataPieceList[rookPosx * 8 + rookPosy] = dataPieceList[rookEndx * 8 + rookPosy];
        dataPieceList[rookEndx * 8 + rookPosy] = PIECE::NONE;
    }
    turn = (CHESS::COLOR) (turn ^ CHESS::BOTHCOLOR);
    history->popMove();
    return true;
}

void Board::NewGame() {
    dataPieceList = std::vector<int>(64, PIECE::NONE);
    dataPieceList[0]  = dataPieceList[56] = PIECE::ROOK + CHESS::WHITE;
    dataPieceList[8]  = dataPieceList[48] = PIECE::KNIGHT + CHESS::WHITE;
    dataPieceList[16] = dataPieceList[40] = PIECE::BISHOP + CHESS::WHITE;
    dataPieceList[24] = PIECE::QUEEN + CHESS::WHITE;
    dataPieceList[32] = PIECE::KING + CHESS::WHITE;
    dataPieceList[7]  = dataPieceList[63] = PIECE::ROOK + CHESS::BLACK;
    dataPieceList[15] = dataPieceList[55] = PIECE::KNIGHT + CHESS::BLACK;
    dataPieceList[23] = dataPieceList[47] = PIECE::BISHOP + CHESS::BLACK;
    dataPieceList[31] = PIECE::QUEEN + CHESS::BLACK;
    dataPieceList[39] = PIECE::KING + CHESS::BLACK;
    for(int i = 0; i < 8; i++) {
        dataPieceList[i * 8 + 1] = PIECE::PAWN + CHESS::WHITE;
        dataPieceList[i * 8 + 6] = PIECE::PAWN + CHESS::BLACK;
    }

    // setup piece
    for(int i = 0; i < 64; i++) {
        pieceList[i]->setPieceData(dataPieceList[i]);
    }

    // setup game status
    gameStatus = GAMESTATUS::NEWGAME;
    turn = CHESS::WHITE;
    winner = CHESS::NONE;

    // setup other
    isPieceSelected = false;
    isPieceHold = false;
    selectedPiecePos = 0;
    prePosition = -1;
    curPosition = -1;
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
                    viewPosList.clear();
                    sf::Vector2i coordChess;
                    coordChess.x = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    coordChess.y = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    int position = coordChess.x * 8 + coordChess.y;
                    if (!isPieceSelected) {
                        if (getPieceColor(position) == turn) {
                            isPieceSelected = true;
                            isPieceHold = true;
                            selectedPiecePos = position;
                            holdPiecePos = position;
                            possiblePosList = getPossibleMove(position);
                        }
                    }
                    else {
                        if (selectedPiecePos == position) {
                            isPieceSelected = false;
                            isPieceHold = true;
                        }
                        else /// when click other pos
                        if (MakeMove(selectedPiecePos, position)) {
                            isPieceSelected = false;
                            prePosition = selectedPiecePos;
                            curPosition = position;
                        }
                        else if (getPieceColor(position) == turn) {
                            isPieceSelected = true;
                            isPieceHold = true;
                            selectedPiecePos = position;
                            holdPiecePos = position;
                            possiblePosList = getPossibleMove(position);
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
                    coordChess.x = (int) (mousePosition.x - boardPosition.x) / (int)cellSize.x;
                    coordChess.y = 7 - (int) (mousePosition.y - boardPosition.y) / (int)cellSize.y;
                    int position = coordChess.x * 8 + coordChess.y;
                    if (isPieceHold) {
                        if (MakeMove(selectedPiecePos, position)) {
                            isPieceSelected = false;
                            isPieceHold = false;
                            selectedPiecePos = 0;
                            prePosition = selectedPiecePos;
                            curPosition = position;
                        }
                        else {
                            isPieceHold = false;
                        }
                    }
                }
                else {
                    isPieceHold = false;
                }
            }
        }
    }
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
    if (turn == CHESS::BLACK) {
        std::vector<Point> possibleMoveList = getAllPossibleMove();
        if (possibleMoveList.size() == 0) {
            printf("End game\n");
            NewGame();
        }
        else {
            Point id = possibleMoveList[rand() % possibleMoveList.size()];
            MakeMove(id.x, id.y);
            isPieceSelected = false;
            isPieceHold = false;
            selectedPiecePos = 0;
            prePosition = id.x;
            curPosition = id.y;
        }
    }
    // if (turn == CHESS::WHITE) {
    //     std::vector<Point> possibleMoveList = getAllPossibleMove();
    //     Point id = possibleMoveList[rand() % possibleMoveList.size()];
    //     if (!MakeMove(id.x, id.y)) {
    //         printf("End game\n");
    //     }
    //     else {
    //         isPieceSelected = false;
    //         isPieceHold = false;
    //         selectedPiecePos = 0;
    //         prePosition = id.x;
    //         curPosition = id.y;
    //     }
    // }
    // sf::sleep(sf::milliseconds(100));

    for(int i = 0; i < 64; i++) {
        pieceList[i]->setPieceData(dataPieceList[i]);
        pieceList[i]->setMouseStatus(MOUSE::NONE);
        boardPrint->setStateCell(i, BoardPrint::COMMON);
    }
    if (ifCheck()) {
        boardPrint->setStateCell(getKingPosition(), BoardPrint::CHECK);
    }
    if (ifCheckMate()) {
        boardPrint->setStateCell(getKingPosition(), BoardPrint::CHECKMATE);
    }
    if (history->getCntMove()) {
        MovingStore lastMove = history->getLastMove();
        boardPrint->setStateCell(lastMove.prePos, BoardPrint::PREMOVE);
        boardPrint->setStateCell(lastMove.curPos, BoardPrint::PREMOVE);
    }
    if (isPieceSelected | isPieceHold) {
        boardPrint->setStateCell(selectedPiecePos, BoardPrint::SELECTED);
        for(int u : possiblePosList) 
            boardPrint->setStateCell(u, BoardPrint::POSSIBLE);
    }
    if (isPieceHold) {
        boardPrint->setStateCell(holdPiecePos, BoardPrint::SELECTED);
        pieceList[holdPiecePos]->setMouseStatus(MOUSE::HOLD, mousePosition);
    }

    boardPrint->update(theme);
    for(int i = 0; i < 64; i++) {
        pieceList[i]->update(theme);
    }
    
}

void Board::render(sf::RenderTarget& target, sf::RenderStates state) const
{
    state = this->state;
    boardPrint->render(target, state);
    std::vector<std::pair<int, int>> piecePriority;
    for(int i = 0; i < 64; i++)
        piecePriority.emplace_back(pieceList[i]->getPriorityPrint(), i);
    std::sort(piecePriority.begin(), piecePriority.end());
    for(std::pair<int, int> data : piecePriority) {
        pieceList[data.second]->render(target, state);
    }
}