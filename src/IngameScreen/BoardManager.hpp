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
#include "../DataControl/Arrow.hpp"
#include "../DataControl/Circle.hpp"
#include "../DataControl/FileInit.hpp"
#include <vector>

class BoardManager : public sf::Drawable {
public:
    BoardManager(Point renderPosition, Point renderSize, Theme* theme);
    ~BoardManager();
    std::string handleEvent(const sf::Event& event);
    std::string update(sf::Time deltaTime);
    void updateRender();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

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

    void setBotHelp(bool isBotHelp);

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
    void setBoardRotate(bool isBoardRotate);

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

    std::vector<bool> isBot;
    bool isCheck;
    bool isCheckMate;
    bool isStaleMate;
    bool isWhiteTurn;

    bool isBotRunning;
    bool isEvent;

    bool isPieceSelected;
    bool isPieceHold;
    int selectedPieceIndex;
    int holdPieceIndex;
    int preSquareIndex, curSquareIndex;
    Point mousePosition;

    bool isNoteHold;
    bool isBoardRotate;
    bool isBotHelp;
    int mode;   /// PvE, EvP, PvP, EvE

    std::vector<int> possibleIndexList; // all squareIndex is prepared to move
    // std::vector<int> noteCircleList;   /// all squareIndex which is right clicked
    std::vector<std::pair<int, int>> noteList; // all arrow from start to target
    std::vector<Move> movesUndoList;

    std::vector<Circle> noteCircleRender;
    std::vector<Arrow> noteArrowRender;

    std::vector<Move> suggestMoves;
};

#endif