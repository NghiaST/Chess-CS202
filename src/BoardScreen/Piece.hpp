#ifndef __Piece_hpp_
#define __Piece_hpp_
#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/Theme.hpp"
#include "../Graphic.hpp"

class Piece : public Graphic {  /// a1 -> a2 -> ... -> b1 -> ...
private:
    int position; // 0 -> 63
    int posx, posy; // 0 -> 7
    int pieceData; // 0 -> 23
    CHESS::COLOR pieceColor;
    PIECE::TYPE pieceType;
    int status; // 0: none, 1: alive, 2: dead, 3: viewed
    MOUSE::STATUS mousestatus; // 0: none, 1: pointed, 2: selected, 3: hold, 4: unpressed

private:
    sf::Sprite sprite;

public:
    Piece(int position, CHESS::COLOR pieceColor, PIECE::TYPE pieceType, int status = 0);
    Piece(int position, int pieceData, int status = 0);
    ~Piece();
    const PIECE::TYPE& getPieceType() const;
    const CHESS::COLOR& getPieceColor() const;
    const int& getPieceData() const;
    void setPieceType(int pieceType);
    void setPieceColor(int pieceColor);
    void setPieceData(int pieceData);
    void setPiece(int pieceColor, int pieceType);
    void setMouseStatus(int mousestatus);
    void setPosition(int position);

public: // front-end
    void update(const Theme* theme) override;
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) override;
};

#endif