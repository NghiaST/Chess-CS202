#ifndef __Board_hpp__
#define __Board_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/StaticButton.hpp"
#include "../DataControl/Button.hpp"
#include "Piece.hpp"
#include "BoardPrint.hpp"
#include "ChessHistory.hpp"
#include <vector>

class Board : public sf::Transformable {
public:
    Board();
    Board(Point renderPosition, Point renderSize, Theme* theme);
    ~Board();
    std::string handleEvent(const sf::Event& event);
    std::string update(sf::Time deltaTime);
    void updateRender();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const;

public:
    // Accessors
    int getGameStatus() const;
    CHESS::COLOR getTurn() const;
    CHESS::COLOR getWinner() const;
    std::vector<int> getAllPieceData() const;
    std::string getStringLastMove() const;
    std::string getStringHistory() const;

    // Mutators
    // void loadGame(std::vector<int> dataPieceList, CHESS::COLOR turn);
    // void loadGameFromHistory(std::vector<MovingStore> moveList);

    // Functions
    bool UndoMove();
    bool MakeMove(int startSquareIndex, int endSquareIndex);
    void NewGame();
    bool ifCheck() const;   /// check if current turn is checked
    bool ifCheckMate() const;  /// check if current turn is checked and no possible move
    bool ifStaleMate() const;  /// check if current turn is not checked and no possible move

private:
    // Process
    const Piece* getPiece(int squareIndex) const;
    const Piece* getPiece(int rank, int file) const;
    const ChessHistory* getHistory() const;
    int getPieceData(int squareIndex) const;
    int getPieceColor(int squareIndex) const;
    int getPieceType(int squareIndex) const;

    // Functions
    bool ifCellAttacked(int squareIndex, int myTurn) const; // check if cell is threaten by the opponent, prevent CASTLE
    bool ifControll(int startSquareIndex, int endSquareIndex) const;  // check if this cell is controlled
    int ifMoveLegalWithoutCheck(int startSquareIndex, int endSquareIndex) const;
    int ifMoveLegalWithoutCheck(int startSquareIndex, int endSquareIndex, std::vector<int> tmpDataPieceList) const; // check if move is legal, except Check
    int ifMoveLegal(int startSquareIndex, int endSquareIndex) const;
    int ifMoveLegal(int startRank, int startFile, int endRank, int endFile) const;
    std::vector<int> getPossibleMove(int startSquareIndex) const;
    std::vector<Point> getAllPossibleMove() const;   /// get all possible move of current turn

    int getKingSquareIndex() const;

    int TryMove(int startSquareIndex, int endSquareIndex);         /// move selected piece to selected squareIndex, without changing visual but changing data. must call undomove() after processing

private:
    sf::Shader shader;
    sf::RenderStates state;
    Theme* theme;
    // list const squareIndex: board, analysis
    Point boardPosition;
    Point boardSize;
    Point cellSize;
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
    std::vector<Piece*> piecePrintList;
    BoardPrint* boardPrint;
    std::vector<int> dataPieceList;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR turn; // 8: white, 16: black
    CHESS::COLOR winner;

    bool isPieceSelected;
    bool isPieceHold;
    int selectedPieceIndex;
    int holdPieceIndex;
    int preSquareIndex, curSquareIndex;
    Point mousePosition;
    std::vector<int> possibleIndexList; // all squareIndex is prepared to move
    std::vector<int> noteViewIndexList;   /// all squareIndex which is right clicked

    /// history of game
    ChessHistory* history;
};

#endif