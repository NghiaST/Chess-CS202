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
    sf::Shader shader;
    sf::RenderStates state;
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
    bool isPieceHold;
    bool isCheck;
    int selectedPiecePos;
    int holdPiecePos;
    int prePosition, curPosition;
    std::vector<int> possiblePosList; // all position is prepared to move
    std::vector<int> viewPosList;   /// all position which is right clicked

    /// history of game
    ChessHistory* history;

public:
    PieceBoard();
    ~PieceBoard();

private:

    const Piece* getPiece(int position) const;
    const Piece* getPiece(int posx, int posy) const;
    const ChessHistory* getHistory() const;
    int getPieceData(int position) const;
    int getPieceColor(int position) const;
    int getPieceType(int position) const;
    std::vector<int> getAllPieceData();

    bool ifCellAttacked(int position, int myTurn) const; // check if cell is threaten by the opponent, prevent CASTLE
    bool ifControll(int startpos, int endpos) const;  // check if this cell is controlled
    int ifMoveLegalWithoutCheck(int startpos, int endpos) const;
    int ifMoveLegalWithoutCheck(int startpos, int endpos, std::vector<int> tmpDataPieceList) const; // check if move is legal, except Check
    int ifMoveLegal(int startpos, int endpos) const;
    int ifMoveLegal(int startx, int starty, int endx, int endy) const;
    std::vector<int> getPossibleMove(int startpos) const;
    std::vector<sf::Vector2i> getAllPossibleMove() const;   /// get all possible move of current turn

    int getKingPosition() const;
    bool ifCheck() const;   /// check if current turn is checked
    bool ifCheckMate() const;  /// check if current turn is checked and no possible move
    bool ifStaleMate() const;  /// check if current turn is not checked and no possible move

    int TryMove(int startpos, int endpos);         /// move selected piece to selected position, without changing visual but changing data. must call undomove() after processing
    bool MakeMove(int startpos, int endpos);
    bool UndoMove();

    void NewGame();

public:
    void handleEvent(const sf::Event& event, const Point mousePos, double eventClock);
    void update();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default);
};

#endif