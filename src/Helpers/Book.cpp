#include <Helpers/Book.hpp>

int Book::getRank(int square) {
    return square / 8;
}

int Book::getFile(int square) {
    return square % 8;
}

int Book::getSquare(int rank, int file) {
    return rank * 8 + file;
}

std::string Book::getSquareName(int square) {
    return getSquareName(getRank(square), getFile(square));
}

std::string Book::getSquareName(int rank, int file) {
    std::string str = "";
    str += (char)('a' + file);
    str += (char)('1' + rank);
    return str;
}

int Book::getSquareFromName(std::string squareName) {
    int file = squareName[0] - 'a';
    int rank = squareName[1] - '1';
    return getSquare(rank, file);
}

bool Book::isCoordinateValid(int rank, int file) {
    return (rank >= 0 && rank < 8 && file >= 0 && file < 8);
}
