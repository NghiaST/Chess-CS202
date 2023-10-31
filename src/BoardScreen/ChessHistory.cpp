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
    if (move.prePos == 38 && move.preData == PIECE::KING + CHESS::BLACK) {
        dataMovingKing[1] += 1;
    }
}

void ChessHistory::undoMove() {
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

MovingStore ChessHistory::getLastMove() const {
    if (cntMove > 0) {
        return moveList[cntMove - 1];
    }
    return MovingStore();
}

bool ChessHistory::isCastlePossible(int color, int side) const {
    return dataMovingKing[color] == 0 && dataMovingRook[color][side] == 0;
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
