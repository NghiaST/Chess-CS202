#ifndef __Piece_hpp_
#define __Piece_hpp_
#include <SFML/Graphics.hpp>
#include "include.hpp"
#include "Graphic.hpp"

class Piece;
class PieceBoard;

class Piece : public Graphic {
private:
    int position; // 0 -> 63
    int posx, posy; // 0 -> 7
    int pieceData; // 0 -> 31
    CHESS::COLOR pieceColor;
    PIECE::TYPE pieceType;
    int status; // 0: none, 1: alive, 2: dead, 3: viewed
    MOUSE::STATUS mousestatus; // 0: none, 1: pointed, 2: selected, 3: hold, 4: unpressed

public:
    Piece(int position, CHESS::COLOR pieceColor, PIECE::TYPE pieceType, int status = 0);
    Piece(int position, int pieceData, int status = 0);
    ~Piece();
    int ifMoveLegal(const PieceBoard* board, int position) const;    //x en passant
    int ifCheck() const;    //x
    const PIECE::TYPE& getPieceType() const;
    const CHESS::COLOR& getPieceColor() const;
    const int& getPieceData() const;
    void setPieceType(int pieceType);
    void setPieceColor(int pieceColor);
    void setPieceData(int pieceData);
    void setPiece(int pieceColor, int pieceType);
    void setPosition(int position);

public: // front-end
    void preparePrint(const Theme* theme) override;  //x
    void print(sf::RenderWindow* window) override;   //x
};

#endif