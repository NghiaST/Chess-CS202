#include "PieceBoard.hpp"

PieceBoard::PieceBoard() {
    pieceList.assign(64, nullptr);
    for(auto it = pieceList.begin(); it != pieceList.end(); ++it) {
        *it = new Piece(std::distance(pieceList.begin(), it), PIECE::NONE);
    }
    gameStatus = 0;
    turn = CHESS::NONE;
    winner = CHESS::NONE;
}

PieceBoard::~PieceBoard() {
    // destructor code here
}

const Piece* PieceBoard::getPiece(int position) const {
    return pieceList[position];
}
const Piece* PieceBoard::getPiece(int posx, int posy) const {
    return getPiece(posx * 8 + posy);
}

int PieceBoard::ifMoveLegal(int startpos, int endpos) const {
    // code to check if move is legal
    return pieceList[startpos]->ifMoveLegal(this, endpos);
}

int PieceBoard::ifMoveLegal(int startx, int starty, int endx, int endy) const {
    // code to check if move is legal
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
