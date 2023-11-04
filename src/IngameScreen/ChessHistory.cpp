#include "ChessHistory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

MovingStore::MovingStore() {
    this->preIndex = -1;
    this->curIndex = -1;
    this->preData = 0;
    this->curData = 0;
    this->moveStatus = 0;
}

MovingStore::MovingStore(int preIndex, int curIndex, int preData, int curData, int moveStatus) {
    this->preIndex = preIndex;
    this->curIndex = curIndex;
    this->preData = preData;
    this->curData = curData;
    this->moveStatus = moveStatus;
}

ChessHistory::ChessHistory() {
    cntMove = 0;
    memset(dataMovingRook, 0, sizeof(dataMovingRook));
    memset(dataMovingKing, 0, sizeof(dataMovingKing));
}

ChessHistory::~ChessHistory() {}

void ChessHistory::addMove(const MovingStore move) {
    moveList.push_back(move);
    cntMove++;
    if (move.preIndex == 0 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][0] += 1;
    }
    if (move.preIndex == 56 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][1] += 1;
    }
    if (move.preIndex == 7 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][0] += 1;
    }
    if (move.preIndex == 63 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][1] += 1;
    }
    if (move.preIndex == 32 && move.preData == PIECE::KING + CHESS::WHITE) {
        dataMovingKing[0] += 1;
    }
    if (move.preIndex == 39 && move.preData == PIECE::KING + CHESS::BLACK) {
        dataMovingKing[1] += 1;
    }
}

void ChessHistory::popMove() {
    if (cntMove == 0) return;
    MovingStore move = moveList.back();
    moveList.pop_back();
    cntMove--;

    if (move.preIndex == 0 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][0] -= 1;
    }
    if (move.preIndex == 56 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][1] -= 1;
    }
    if (move.preIndex == 7 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][0] -= 1;
    }
    if (move.preIndex == 63 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][1] -= 1;
    }
    if (move.preIndex == 4 && move.preData == PIECE::KING + CHESS::WHITE) {
        dataMovingKing[0] -= 1;
    }
    if (move.preIndex == 60 && move.preData == PIECE::KING + CHESS::BLACK) {
        dataMovingKing[1] -= 1;
    }
}

void ChessHistory::loadHistory(std::string filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string encoded;
    std::getline(fin, encoded);
    fin.close();

    moveList = decodeHistory(encoded);
    cntMove = moveList.size();
}

void ChessHistory::saveHistory(std::string filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string encoded = encodeHistory();
    fout << encoded << std::endl;
    fout.close();
}

void ChessHistory::clear() {
    cntMove = 0;
    moveList.clear();
    memset(dataMovingRook, 0, sizeof(dataMovingRook));
    memset(dataMovingKing, 0, sizeof(dataMovingKing));
}

int ChessHistory::getCntMove() const {
    return cntMove;
}

MovingStore ChessHistory::getLastMove() const {
    if (cntMove > 0) {
        return moveList[cntMove - 1];
    }
    return MovingStore();
}

bool ChessHistory::isCastlePossible(int color, int side) const {
    return dataMovingKing[color] == 0 && dataMovingRook[color][side] == 0;
}

std::string ChessHistory::getStringLastMove() const
{
    if (cntMove == 0) return "";
    MovingStore move = moveList[cntMove - 1];
    std::string str = "";

    std::map<int, char> mp;
    mp[PIECE::KNIGHT] = 'N';
    mp[PIECE::BISHOP] = 'B';
    mp[PIECE::ROOK] = 'R';
    mp[PIECE::QUEEN] = 'Q';
    mp[PIECE::KING] = 'K';
    
    static int ENPASSANT = 2, CASTLE = 3;
    if (move.moveStatus == CASTLE) {
        if (move.curIndex % 8 == 6) return "O-O";
        if (move.curIndex % 8 == 2) return "O-O-O";
    }
    else if ((move.preData & 7) != PIECE::PAWN) {
        str = mp[move.preData & 7];
    }
    if (move.curData != PIECE::NONE || move.moveStatus == ENPASSANT) {
        str += "x";
    }
    str += (char)('a' + move.curIndex % 8);
    str += (char)('1' + move.curIndex / 8);
    return str;
}

std::string ChessHistory::getStringHistory() const
{
    std::string str = "";
    for (int i = 0; i < cntMove; i++) {
        if (i % 2 == 0) str += std::to_string(i / 2 + 1) + ". ";
        else str += " ";
        str += getStringLastMove();
        if (i % 2 == 1) str += "\n";
    }
    return str;
}

std::string ChessHistory::encodeHistory() {
    std::string encoded;
    for (int i = 0; i < cntMove; i++) {
        MovingStore move = moveList[i];
        encoded += std::to_string(move.preIndex) + " ";
        encoded += std::to_string(move.preData) + " ";
        encoded += std::to_string(move.curIndex) + " ";
        encoded += std::to_string(move.curData) + " ";
        encoded += std::to_string(move.moveStatus) + " ";
    }
    return encoded;
}

std::vector<MovingStore> ChessHistory::decodeHistory(std::string encoded) {
    std::vector<MovingStore> decoded;
    std::stringstream ss(encoded);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        int preIndex = std::stoi(token);
        std::getline(ss, token, ' ');
        int preType = std::stoi(token);
        std::getline(ss, token, ' ');
        int curIndex = std::stoi(token);
        std::getline(ss, token, ' ');
        int curData = std::stoi(token);
        std::getline(ss, token, ' ');
        int moveStatus = std::stoi(token);

        MovingStore move(preIndex, preType, curIndex, curData, moveStatus);
        decoded.push_back(move);
    }

    return decoded;
}
