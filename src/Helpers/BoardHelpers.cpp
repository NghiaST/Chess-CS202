#include "BoardHelpers.hpp"
#include "../DataControl/Include.hpp"

const int BoardHelpers::a1 = 0;
const int BoardHelpers::b1 = 1;
const int BoardHelpers::c1 = 2;
const int BoardHelpers::d1 = 3;
const int BoardHelpers::e1 = 4;
const int BoardHelpers::f1 = 5;
const int BoardHelpers::g1 = 6;
const int BoardHelpers::h1 = 7;

const int BoardHelpers::a8 = 56;
const int BoardHelpers::b8 = 57;
const int BoardHelpers::c8 = 58;
const int BoardHelpers::d8 = 59;
const int BoardHelpers::e8 = 60;
const int BoardHelpers::f8 = 61;
const int BoardHelpers::g8 = 62;
const int BoardHelpers::h8 = 63;

std::string BoardHelpers::fileNames = "abcdefgh";
std::string BoardHelpers::rankNames = "12345678";

std::string BoardHelpers::SquareNameFromIndex(int index) {
    std::string name = "";
    name += (char)('a' + (index & 7));
    name += (char)('1' + (index >> 3));
    return name;
}

std::string BoardHelpers::SquareNameFromCoord(int rank, int file) {
    std::string name = "";
    name += (char)('a' + file);
    name += (char)('1' + rank);
    return name;
}

char BoardHelpers::RankName(int rank) {
    return '1' + rank;
}

char BoardHelpers::FileName(int file) {
    return 'a' + file;
}

int BoardHelpers::SquareIndexFromName(std::string name) {
    int file = name[0] - 'a';
    int rank = name[1] - '1';
    return rank * 8 + file;
}

int BoardHelpers::FileID(int square) {
    return square & 7;
}

int BoardHelpers::RankID(int square) {
    return square >> 3;
}

Point BoardHelpers::CoordFromID(int index) {
    return Point(index >> 3, index & 7);
}
