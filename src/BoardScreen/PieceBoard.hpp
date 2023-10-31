#ifndef __PieceBoard_hpp__
#define __PieceBoard_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "Piece.hpp"
#include "Board.hpp"
#include "ChessHistory.hpp"
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
    enum MOVESTATUS {
        ILLEGAL = 0,
        LEGAL = 1,
        ENPASSANT = 2,
        CASTLE = 3
    };
private:
    std::vector<Piece*> pieceList;
    Board* board;
    std::vector<int> dataPieceList;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR turn; // 8: white, 16: black
    CHESS::COLOR winner;

    bool isPieceSelected;
    int selectedPiecePos;
    std::vector<int> possiblePosList; // all position is prepared to move
    bool isCheck;

    /// history of game
    ChessHistory* history;

public:
    PieceBoard();
    ~PieceBoard();
    const Piece* getPiece(int position) const;
    const Piece* getPiece(int posx, int posy) const;
    const ChessHistory* getHistory() const;
    std::vector<int> getAllPieceData();

    // bool isBoardLegal(std::vector<int> dataPieceList) const;
    int ifMoveLegalThisTurn(int startpos, int endpos) const;
    int ifMoveLegalThisTurn(int startpos, int endpos, std::vector<int> tmpDataPieceList) const;
    int ifMoveLegal(int startpos, int endpos) const;
    int ifMoveLegal(int startx, int starty, int endx, int endy) const;
    std::vector<int> getPossibleMove(int startpos) const;
    std::vector<sf::Vector2i> getAllPossibleMove() const;

    bool ifCheck() const;
    bool ifCheckMate() const;


    void MakeMove(int startpos, int endpos);
    void MakeMove(int startx, int starty, int endx, int endy); //x, y -> x', y'

    void NewGame();

public:
    void handleEvent(const sf::Event& event, const Point mousePos, double eventClock);
    void update();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default);
};

#endif