#ifndef __Piece2_hpp_
#define __Piece2_hpp_
#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/Theme.hpp"
#include "../Graphic.hpp"

class Piece2 {  /// a1 -> a2 -> ... -> b1 -> ...
public:


private:
    int index; // 0 -> 63
    int rank, file; // 0 -> 7
    int pieceData; // 0 -> 23



    CHESS::COLOR pieceColor;
    PIECE::TYPE pieceType;
    int status; // 0: none, 1: alive, 2: dead, 3: viewed
    MOUSE::STATUS mousestatus; // 0: none, 1: pointed, 2: selected, 3: hold, 4: unpressed
    Point mousePosition;

private:
    sf::Sprite sprite;

public:
    Piece(int index, CHESS::COLOR pieceColor, PIECE::TYPE pieceType, int status = 0);
    Piece(int index, int pieceData, int status = 0);
    ~Piece();
    const PIECE::TYPE& getPieceType() const;
    const CHESS::COLOR& getPieceColor() const;
    const int& getPieceData() const;
    void setPieceData(int pieceData);
    void setPiece(int pieceColor, int pieceType);
    void setMouseStatus(int mousestatus, Point mousePosition = Point(0, 0));
    void setIndex(int index);

public: // front-end
    void update(const Theme* theme);
    void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) override override;
};

#endif