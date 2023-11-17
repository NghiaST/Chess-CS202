#ifndef __BoardHelpers_hpp__
#define __BoardHelpers_hpp__

#include <string>
struct Point;

class BoardHelpers {
public:
    static std::string SquareNameFromIndex(int index);
    static std::string SquareNameFromCoord(int rank, int file);
    static char RankName(int rank);
    static char FileName(int file);
    static int SquareIndexFromName(std::string name);

    static int FileID(int square);
    static int RankID(int square);

    static Point CoordFromID(int index);

public:
    static const int a1;
    static const int b1;
    static const int c1;
    static const int d1;
    static const int e1;
    static const int f1;
    static const int g1;
    static const int h1;

    static const int a8;
    static const int b8;
    static const int c8;
    static const int d8;
    static const int e8;
    static const int f8;
    static const int g8;
    static const int h8;
    static std::string fileNames;
    static std::string rankNames;
};

#endif