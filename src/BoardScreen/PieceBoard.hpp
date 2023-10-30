#ifndef __PieceBoard_hpp__
#define __PieceBoard_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "Piece.hpp"
#include "Board.hpp"
#include <vector>

class PieceBoard {
private:
    Theme* theme;
    // list const position: board, analysis
    Point boardPosition;
    Point boardSize;
    enum GAMESTATUS {
        NONE = 0,
        NEWGAME = 1,
        ONGOING = 2,
        ENDGAME = 3
    };
private:
    std::vector<Piece*> pieceList;
    Board* board;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR turn; // 8: white, 16: black
    CHESS::COLOR winner;

    bool isPieceSelected;
    int selectedPiecePos;
    std::vector<int> possiblePosList; // all position is prepared to move
    /// may add history of game
    int prePosition;
    int curPosition;

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
    void handleEvent(const sf::Event& event, const Point mousePos, double eventClock);
    void update();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default);
};

#endif