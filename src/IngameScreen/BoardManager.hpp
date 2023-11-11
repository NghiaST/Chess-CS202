#ifndef __BoardManager_hpp__
#define __BoardManager_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/StaticButton.hpp"
#include "../DataControl/Button.hpp"
#include "Piece.hpp"
#include "BoardPrint.hpp"
#include "NewBoard.hpp"
#include "Bot.hpp"
#include <vector>

class BoardManager {
public:
    BoardManager(Point renderPosition, Point renderSize, Theme* theme);
    ~BoardManager();
    std::string handleEvent(const sf::Event& event);
    std::string update(sf::Time deltaTime);
    void updateRender();
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const;

public:
    // Accessors
    int getGameStatus() const;
    CHESS::COLOR getTurn() const;
    int getResult() const;
    bool ifBotTurn() const;
    bool ifCheckMate() const;
    bool ifStaleMate() const;
    bool ifEndGame() const;
    const NewBoard& getBoard() const;

    // Modifiers
    void NewGame();
    void Undo();
    void Redo();

public:
    enum GAMESTATUS {
        NONE = 0,
        NEWGAME = 1,
        ONGOING = 2,
        ENDGAME = 3
    };

private:
    bool ManagerMove(int startSquare, int targetSquare);
    std::vector<int> getLegalIndexAt(int squareIndex);

private:
    void freshState();

private:
    NewBoard* board;

    sf::Shader shader;
    sf::RenderStates state;
    Theme* theme;
    // list const squareIndex: board, analysis
    Point boardPosition;
    Point boardSize;
    Point cellSize;

private:
    std::vector<Piece*> piecePrintList;
    Bot* bot;
    BoardPrint* boardPrint;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR gameResult; // 0: none, 1: white win, 2: black win, 3: draw

    bool isBot[2];
    bool isCheck;
    bool isCheckMate;
    bool isStaleMate;
    bool isWhiteTurn;

    bool isBotRunning;

    bool isPieceSelected;
    bool isPieceHold;
    int selectedPieceIndex;
    int holdPieceIndex;
    int preSquareIndex, curSquareIndex;
    Point mousePosition;
    std::vector<int> possibleIndexList; // all squareIndex is prepared to move
    std::vector<int> noteViewIndexList;   /// all squareIndex which is right clicked
    std::vector<Move> movesUndoList;
};

#endif