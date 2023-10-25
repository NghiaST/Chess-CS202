#ifndef __PieceBoard_hpp__
#define __PieceBoard_hpp__

#include <SFML/Graphics.hpp>
#include "include.hpp"
#include "Piece.hpp"
#include "Board.hpp"
#include <vector>

struct PieceBoard : public Graphic {
private:
    std::vector<Piece*> pieceList;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR turn; // 8: white, 16: black
    CHESS::COLOR winner;

public:
    PieceBoard();
    ~PieceBoard();
    const Piece* getPiece(int position) const;
    const Piece* getPiece(int posx, int posy) const;

    int ifMoveLegal(int, int) const;
    int ifMoveLegal(int, int, int, int) const;
    
    void MakeMove(int, int);
    void MakeMove(int, int, int, int); //x, y -> x', y'

public:
    void update();
    void preparePrint(const Theme* theme) override;  //x
    void print(sf::RenderWindow* window) override;   //x
};

#endif