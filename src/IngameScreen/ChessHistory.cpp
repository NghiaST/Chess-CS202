#include "ChessHistory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

MovingStore::MovingStore() {
    this->prePos = -1;
    this->curPos = -1;
    this->preData = 0;
    this->curData = 0;
    this->moveStatus = 0;
}

MovingStore::MovingStore(int prePos, int curPos, int preData, int curData, int moveStatus) {
    this->prePos = prePos;
    this->curPos = curPos;
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
    if (move.prePos == 0 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][0] += 1;
    }
    if (move.prePos == 56 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][1] += 1;
    }
    if (move.prePos == 7 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][0] += 1;
    }
    if (move.prePos == 63 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][1] += 1;
    }
    if (move.prePos == 32 && move.preData == PIECE::KING + CHESS::WHITE) {
        dataMovingKing[0] += 1;
    }
    if (move.prePos == 39 && move.preData == PIECE::KING + CHESS::BLACK) {
        dataMovingKing[1] += 1;
    }
}

void ChessHistory::popMove() {
    if (cntMove == 0) return;
    MovingStore move = moveList.back();
    moveList.pop_back();
    cntMove--;

    if (move.prePos == 0 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][0] -= 1;
    }
    if (move.prePos == 56 && move.preData == PIECE::ROOK + CHESS::WHITE) {
        dataMovingRook[0][1] -= 1;
    }
    if (move.prePos == 7 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][0] -= 1;
    }
    if (move.prePos == 63 && move.preData == PIECE::ROOK + CHESS::BLACK) {
        dataMovingRook[1][1] -= 1;
    }
    if (move.prePos == 4 && move.preData == PIECE::KING + CHESS::WHITE) {
        dataMovingKing[0] -= 1;
    }
    if (move.prePos == 60 && move.preData == PIECE::KING + CHESS::BLACK) {
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
        if (move.curPos == 62) return "O-O";
        if (move.curPos == 58) return "O-O-O";
    }
    else if ((move.preData & 7) != PIECE::PAWN) {
        str = mp[move.preData & 7];
    }
    if (move.curData != PIECE::NONE || move.moveStatus == ENPASSANT) {
        str += "x";
    }
    str += (char)('a' + move.curPos % 8);
    str += (char)('1' + move.curPos / 8);
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
        encoded += std::to_string(move.prePos) + " ";
        encoded += std::to_string(move.preData) + " ";
        encoded += std::to_string(move.curPos) + " ";
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
        int prePos = std::stoi(token);
        std::getline(ss, token, ' ');
        int preType = std::stoi(token);
        std::getline(ss, token, ' ');
        int curPos = std::stoi(token);
        std::getline(ss, token, ' ');
        int curData = std::stoi(token);
        std::getline(ss, token, ' ');
        int moveStatus = std::stoi(token);

        MovingStore move(prePos, preType, curPos, curData, moveStatus);
        decoded.push_back(move);
    }

    return decoded;
}
