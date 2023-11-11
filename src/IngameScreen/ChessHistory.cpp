#include "ChessHistory.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

ChessHistory::ChessHistory() {
    unknownMove = 0;
    cntMove = 0;
    memset(castlingRights, 0, sizeof(castlingRights));
}

ChessHistory::~ChessHistory() {}

void ChessHistory::addMove(const Move move) {
    moveList.push_back(move);
    cntMove++;

    if (move.startPiece == PIECE::WhiteKing) {
        castlingRights[0] = cntMove;
        castlingRights[1] = cntMove;
    }
    if (move.startPiece == PIECE::BlackKing) {
        castlingRights[2] = cntMove;
        castlingRights[3] = cntMove;
    }
    if (move.startPiece == PIECE::WhiteRook && move.startSquare == 0) {
        castlingRights[0] = cntMove;
    }
    if (move.startPiece == PIECE::WhiteRook && move.startSquare == 7) {
        castlingRights[1] = cntMove;
    }
    if (move.startPiece == PIECE::BlackRook && move.startSquare == 56) {
        castlingRights[2] = cntMove;
    }
    if (move.startPiece == PIECE::BlackRook && move.startSquare == 63) {
        castlingRights[3] = cntMove;
    }
}

void ChessHistory::popMove() {
    if (cntMove <= unknownMove) return;
    Move move = moveList.back();
    moveList.pop_back();
    cntMove--;
    
    for(int i = 0; i < 4; i++) {
        if (castlingRights[i] > cntMove) {
            castlingRights[i] = 0;
        }
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
    unknownMove = 0;
    cntMove = 0;
    moveList.clear();
    memset(castlingRights, 0, sizeof(castlingRights));
}

int ChessHistory::getCntMove() const {
    return cntMove;
}

Move ChessHistory::getLastMove() const {
    if (unknownMove < cntMove) {
        return moveList[cntMove - 1];
    }
    return Move();
}

bool ChessHistory::isCastlePossible(int color, int side) const {
    return castlingRights[color * 2 + side] == 0;
}

std::string ChessHistory::getStringMove(int index) const
{
    if (index < unknownMove) return "";
    Move move = moveList[cntMove - unknownMove + index];
    std::string str = "";

    std::map<int, char> mp;
    mp[PIECE::Knight] = 'N';
    mp[PIECE::Bishop] = 'B';
    mp[PIECE::Rook] = 'R';
    mp[PIECE::Queen] = 'Q';
    mp[PIECE::King] = 'K';
    
    static int ENPASSANT = 2, CASTLE = 3;
    if (move.flag == CASTLE) {
        if (move.targetSquare % 8 == 6) return "O-O";
        if (move.targetSquare % 8 == 2) return "O-O-O";
    }
    else if ((move.startPiece & 7) != PIECE::Pawn) {
        str = mp[move.startPiece & 7];
    }
    if (move.targetPiece != PIECE::None || move.flag == ENPASSANT) {
        str += "x";
    }
    str += (char)('a' + move.targetSquare % 8);
    str += (char)('1' + move.targetSquare / 8);
    return str;
}

std::string ChessHistory::getStringLastMove() const
{
    return getStringMove(cntMove - 1);
}

std::string ChessHistory::getStringHistory() const
{
    std::string str = "";
    for(int i = 0; i < cntMove; i++) {
        if (i % 2 == 0) str += std::to_string(i / 2 + 1) + ". ";
        else str += " ";
        str += getStringMove(i);
        if (i % 2 == 1) str += "\n";
    }
    return str;
}

std::string ChessHistory::encodeHistory() {
    std::string encoded;
    for (int i = 0; i < cntMove; i++) {
        Move move = moveList[i];
        encoded += std::to_string(move.startSquare) + " ";
        encoded += std::to_string(move.startPiece) + " ";
        encoded += std::to_string(move.targetSquare) + " ";
        encoded += std::to_string(move.targetPiece) + " ";
        encoded += std::to_string(move.flag) + " ";
    }
    return encoded;
}

std::vector<GeneralMove> ChessHistory::decodeHistory(std::string encoded) {
    std::vector<GeneralMove> decoded;
    std::stringstream ss(encoded);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        int startSquare = std::stoi(token);
        std::getline(ss, token, ' ');
        int preType = std::stoi(token);
        std::getline(ss, token, ' ');
        int targetSquare = std::stoi(token);
        std::getline(ss, token, ' ');
        int targetPiece = std::stoi(token);
        std::getline(ss, token, ' ');
        int flag = std::stoi(token);

        GeneralMove move(startSquare, preType, targetSquare, targetPiece, flag);
        decoded.push_back(move);
    }

    return decoded;
}
