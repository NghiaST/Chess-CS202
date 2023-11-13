#ifndef __Piece_hpp_
#define __Piece_hpp_
#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/Theme.hpp"
#include "../Graphic.hpp"

class Piece : public Graphic {  /// a1 -> a2 -> ... -> b1 -> ...
private:
    int index;      // 0 -> 63
    int rank, file; // 0 -> 7
    int piece;      // 0 - 23
    int status;     // 0: none, 1: moved
    MOUSE::STATUS mousestatus; // 0: none, 1: pointed, 2: selected, 3: hold, 4: unpressed
    Point mousePosition;

private:
    sf::Sprite sprite;

public:
    Piece(int index, int pieceData, int status = 0);
    ~Piece();
    int getPiece() const;
    void setPiece(int piece);
    void setPiece(int pieceColor, int pieceType);
    void setMouseStatus(int mousestatus, Point mousePosition = Point(0, 0));
    void setIndex(int index);

public: // front-end
    void update(const Theme* theme);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};

#endif