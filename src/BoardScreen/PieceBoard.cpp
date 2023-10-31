#include "PieceBoard.hpp"
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

PieceBoard::PieceBoard() {
    theme = new Theme();
    pieceList.assign(64, nullptr);
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
        *it = new Piece(std::distance(pieceList.begin(), it), PIECE::NONE);
    }
    board = new Board();
    gameStatus = 1;
    turn = CHESS::NONE;
    winner = CHESS::NONE;

    history = new ChessHistory();
    dataPieceList.assign(64, PIECE::NONE);

    boardPosition = Point(20, 20);
    boardSize = Point(60, 60);
    NewGame();
}

PieceBoard::~PieceBoard() {
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
        delete *it;
    }
}

const Piece* PieceBoard::getPiece(int position) const {
    return pieceList[position];
}
const Piece* PieceBoard::getPiece(int posx, int posy) const {
    return getPiece(posx * 8 + posy);
}

const ChessHistory* PieceBoard::getHistory() const {
    return history;
}

std::vector<int> PieceBoard::getAllPieceData()
{
    std::vector<int> res;
    for(int i = 0; i < 64; i++) {
        res.push_back(pieceList[i]->getPieceData());
    }
    return res;
}

int PieceBoard::ifMoveLegalThisTurn(int startpos, int endpos) const {
    return ifMoveLegalThisTurn(startpos, endpos, dataPieceList);
}
int PieceBoard::ifMoveLegalThisTurn(int startpos, int endpos, std::vector<int> tmpDataPieceList) const
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

    sf::Vector2i startCoord(startpos / 8, startpos % 8);
    sf::Vector2i endCoord(endpos / 8, endpos % 8);
    sf::Vector2i diff = endCoord - startCoord;
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
            int totaldiff = abs(diff.x) | abs(diff.y);
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
            if (curPieceColor ^ pieceColor == CHESS::BLACKWHITE) {
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

int PieceBoard::ifMoveLegal(int startpos, int endpos) const {
    int status = ifMoveLegalThisTurn(startpos, endpos);
    if (status == ILLEGAL) return status;

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
        if (ifMoveLegalThisTurn(i, kingPos, newDataPieceList) != ILLEGAL) {
            return ILLEGAL;
        }
    }
    return status;
}

int PieceBoard::ifMoveLegal(int startx, int starty, int endx, int endy) const {
    return ifMoveLegal(startx * 8 + starty, endx * 8 + endy);
}

std::vector<int> PieceBoard::getPossibleMove(int startpos) const
{
    std::vector<int> legalMove;
    for (int i = 0; i < 64; i++) {
        if (ifMoveLegal(startpos, i) != ILLEGAL) {
            legalMove.push_back(i);
        }
    }
    return legalMove;
}

std::vector<sf::Vector2i> PieceBoard::getAllPossibleMove() const
{
    std::vector<sf::Vector2i> legalMove;
    for(int i = 0; i < 64; i++)
    for (int j = 0; j < 64; j++) {
        if (ifMoveLegal(i, j)) {
            legalMove.push_back(sf::Vector2i(i, j));
        }
    }
    return legalMove;
}

bool PieceBoard::ifCheck() const {
    int kingPos = -1;
    for(int i = 0; i < 64; i++) {
        if (dataPieceList[i] == (PIECE::KING + turn)) {
            kingPos = i;
            break;
        }
    }
    for(int i = 0; i < 64; i++) {
        if (ifMoveLegalThisTurn(i, kingPos) != ILLEGAL) {
            return true;
        }
    }
    return false;
}

void PieceBoard::MakeMove(int startpos, int endpos) {
    printf("%d %d\n", startpos, endpos);
    int status = ifMoveLegal(startpos, endpos);
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
    turn = (CHESS::COLOR) (turn ^ CHESS::ALLCOLOR);
}

void PieceBoard::MakeMove(int startx, int starty, int endx, int endy) {
    // code to make move on the board
    MakeMove(startx * 8 + starty, endx * 8 + endy);
}

void PieceBoard::NewGame() {
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

    // setup render
    board->setRenderPosition(boardPosition);
    board->setRenderSize(boardSize * 8);
    for(int i = 0; i < 64; i++) {
        pieceList[i]->setRenderPosition(boardPosition);
        pieceList[i]->setRenderSize(boardSize);
    }
}

void PieceBoard::handleEvent(const sf::Event& event, const Point mousePos, double eventClock) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (gameStatus == NEWGAME || gameStatus == ONGOING) {
                if (board->isMouseOn(mousePos)) {
                    Point coordChess;
                    coordChess.x = (int) (mousePos.x - boardPosition.x) / (int)boardSize.x;
                    coordChess.y = 7 - (int) (mousePos.y - boardPosition.y) / (int)boardSize.y;
                    int position = coordChess.x * 8 + coordChess.y;
                    if (!isPieceSelected) {
                        if (getPiece(position)->getPieceColor() == turn) {
                            isPieceSelected = true;
                            selectedPiecePos = position;
                            possiblePosList = getPossibleMove(position);
                        }
                    }
                    else {
                        if (selectedPiecePos == position) {
                            isPieceSelected = false;
                            possiblePosList.clear();
                        }
                        else /// when click other pos
                        if (board->getStateCell(position) == Board::POSSIBLE || board->getStateCell(position) == Board::POSSIBLE_CAPTURE) {
                            int prePosition = selectedPiecePos;
                            int curPosition = position;
                            isPieceSelected = false;
                            selectedPiecePos = 0;
                            MakeMove(prePosition, curPosition);
                        }
                        else if (getPiece(position)->getPieceColor() == turn) {
                            isPieceSelected = true;
                            selectedPiecePos = position;
                            possiblePosList = getPossibleMove(position);
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < 64; i++) {
        pieceList[i]->setPieceData(dataPieceList[i]);
        board->setStateCell(i, Board::COMMON);
    }
    if (isPieceSelected) {
        board->setStateCell(selectedPiecePos, Board::SELECTED);
        for(int u : possiblePosList) 
            board->setStateCell(u, Board::POSSIBLE);
    }

    // add: check, checkmate
}

void PieceBoard::update() {
    board->update(theme);
    for(int i = 0; i < 64; i++) {
        if (pieceList[i]->getPieceData() != PIECE::NONE) {
            pieceList[i]->update(theme);
        }
    }
}

void PieceBoard::render(sf::RenderTarget& target, sf::RenderStates state)
{
    board->render(target);
    for(int i = 0; i < 64; i++) {
        if (pieceList[i]->getPieceData() != PIECE::NONE) {
            pieceList[i]->render(target);
        }
    }
}