#include "PieceBoard.hpp"

PieceBoard::PieceBoard() {
    pieceList.assign(64, nullptr);
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
        *it = new Piece(std::distance(pieceList.begin(), it), PIECE::NONE);
    }
    board = new Board();
    gameStatus = 1;
    turn = CHESS::NONE;
    winner = CHESS::NONE;

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

int PieceBoard::ifMoveLegal(int startpos, int endpos) const {
    return pieceList[startpos]->ifMoveLegal(this, endpos);
}

int PieceBoard::ifMoveLegal(int startx, int starty, int endx, int endy) const {
    return ifMoveLegal(startx * 8 + starty, endx * 8 + endy);
}

void PieceBoard::MakeMove(int startpos, int endpos) {
    if (!ifMoveLegal(startpos, endpos)) {
        printf("Illegal move!\n");
        exit(1);
    }
/* have not code: if en passant, delete the pawn*/
    pieceList[endpos]->setPieceData(pieceList[startpos]->getPieceData());
    pieceList[startpos]->setPieceData(PIECE::NONE);
}

void PieceBoard::MakeMove(int startx, int starty, int endx, int endy) {
    // code to make move on the board
    MakeMove(startx * 8 + starty, endx * 8 + endy);
}

void PieceBoard::NewGame() {
    std::vector<int> pieceID(64, PIECE::NONE);
    pieceID[0] = pieceID[56] = PIECE::ROOK + CHESS::WHITE;
    pieceID[8] = pieceID[48] = PIECE::KNIGHT + CHESS::WHITE;
    pieceID[16] = pieceID[40] = PIECE::BISHOP + CHESS::WHITE;
    pieceID[24] = PIECE::QUEEN + CHESS::WHITE;
    pieceID[32] = PIECE::KING + CHESS::WHITE;
    pieceID[7] = pieceID[63] = PIECE::ROOK + CHESS::BLACK;
    pieceID[15] = pieceID[55] = PIECE::KNIGHT + CHESS::BLACK;
    pieceID[23] = pieceID[47] = PIECE::BISHOP + CHESS::BLACK;
    pieceID[31] = PIECE::QUEEN + CHESS::BLACK;
    pieceID[39] = PIECE::KING + CHESS::BLACK;
    for(int i = 0; i < 8; i++) {
        pieceID[i * 8 + 1] = PIECE::PAWN + CHESS::WHITE;
        pieceID[i * 8 + 6] = PIECE::PAWN + CHESS::BLACK;
    }

    for(int i = 0; i < 64; i++) {
        pieceList[i]->setPieceData(pieceID[i]);
    }
    gameStatus = 1;
    turn = CHESS::WHITE;
    winner = CHESS::NONE;
}

void PieceBoard::update(FrontEnd* frontEnd) {
    return;
}

void PieceBoard::preparePrint(const Theme* theme) {
    board->preparePrint(theme);
    for(int i = 0; i < 64; i++) {
        if (pieceList[i]->getPieceData() != PIECE::NONE) {
            pieceList[i]->preparePrint(theme);
        }
    }
}

void PieceBoard::print(sf::RenderWindow* window) {
    board->print(window);
    for(int i = 0; i < 64; i++) {
        if (pieceList[i]->getPieceData() != PIECE::NONE) {
            pieceList[i]->print(window);
        }
    }
}