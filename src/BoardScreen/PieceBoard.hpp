#ifndef __PieceBoard_hpp__
#define __PieceBoard_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "Piece.hpp"
#include "Board.hpp"
#include "../DataControl/Event.hpp"
#include <vector>

class PieceBoard {
private:
    Theme* theme;
private:
    std::vector<Piece*> pieceList;
    Board* board;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR turn; // 8: white, 16: black
    CHESS::COLOR winner;

    bool isPieceSelected;
    int selectedPiecePos;

    bool isPieceMoving;
    int movingPiecePos;

public:
    PieceBoard();
    ~PieceBoard();
    const Piece* getPiece(int position) const;
    const Piece* getPiece(int posx, int posy) const;

    int ifMoveLegal(int startpos, int endpos) const;
    int ifMoveLegal(int startx, int starty, int endx, int endy) const;

    void MakeMove(int startpos, int endpos);
    void MakeMove(int startx, int starty, int endx, int endy); //x, y -> x', y'

    void NewGame();

public:
    void handleEvent(Event* event);
    void update();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default);
};

#endif