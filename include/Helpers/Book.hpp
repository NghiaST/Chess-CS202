#ifndef __Book_hpp__
#define __Book_hpp__

#include <string>

class Book {
public:
    static const int a1 = 0;
    static const int b1 = 1;
    static const int c1 = 2;
    static const int d1 = 3;
    static const int e1 = 4;
    static const int f1 = 5;
    static const int g1 = 6;
    static const int h1 = 7;
    
    static const int a8 = 56;
    static const int b8 = 57;
    static const int c8 = 58;
    static const int d8 = 59;
    static const int e8 = 60;
    static const int f8 = 61;
    static const int g8 = 62;
    static const int h8 = 63;

    static int getRank(int square);
    static int getFile(int square);
    static int getSquare(int rank, int file);
    static std::string getSquareName(int square);
    static std::string getSquareName(int rank, int file);
    static int getSquareFromName(std::string squareName);
    static bool isCoordinateValid(int rank, int file);
};

#endif