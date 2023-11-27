#ifndef __PiecePrint_hpp_
#define __PiecePrint_hpp_

#include <Graphic.hpp>
#include <DataControl/Image.hpp>
#include <DataControl/Include.hpp>
#include <DataControl/Theme.hpp>
#include <SFML/Graphics.hpp>

class PiecePrint : public ImageActive {  /// a1 -> a2 -> ... -> b1 -> ...
public:
    PiecePrint();
    PiecePrint(int index, int piece, int status = 0);
    PiecePrint(Point boardPosition, Point renderSize, int index, int piece, int status = 0);
    ~PiecePrint();
    int getPiece() const;
    void setPiece(int piece);
    void setPiece(int pieceColor, int pieceType);
    void setIndex(int index);
    void setBoardPosition(Point boardPosition);
    void updatePosition();

private:
    int index;      // 0 -> 63
    int rank, file; // 0 -> 7
    int piece;      // 0 - 23
    Point boardPosition;
};

#endif