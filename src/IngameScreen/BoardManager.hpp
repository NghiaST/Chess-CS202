#ifndef __BoardManager_hpp__
#define __BoardManager_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../DataControl/TextBox.hpp"
#include "../DataControl/Button.hpp"
#include "PiecePrint.hpp"
#include "BoardPrint.hpp"
#include "PromotionManager.hpp"
#include "../ChessBoard/Bot.hpp"
#include "../DataControl/Arrow.hpp"
#include "../DataControl/Circle.hpp"
#include "../DataControl/FileInit.hpp"
#include "../ChessBoard/Board.hpp"
#include "../DataControl/GameSettings.hpp"
#include "../DataControl/GameAttributes.hpp"
#include <vector>

class BoardManager : public sf::Drawable {
public:
    BoardManager(Point renderPosition, Point renderSize);
    ~BoardManager();
    std::string handleEvent(const sf::Event& event);
    std::string update(sf::Time deltaTime);
    void updateRender();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

public:
    // Accessors
    bool ifBoardRotate() const;
    int getGameStatus() const;
    CHESS::COLOR getTurn() const;
    int getResult() const;
    bool ifBotTurn() const;
    bool ifCheckMate() const;
    bool ifStaleMate() const;
    bool ifEndGame() const;
    const Board& getBoard() const;

    // Modifiers
    void NewGame();
    void Reload();
    void Undo();
    void Redo();

    void setBotHelp(bool isBotHelp);

public:
    enum GAMESTATUS {
        NONE = 0,
        NONSTART = 1,
        ONGOING = 2,
        ENDGAME = 3
    };

private:
    void MakeCorrectMove(Move move);
    bool ManageMove(int startSquare, int targetSquare, bool isBotMove = false);
    std::vector<int> getLegalIndexAt(int squareIndex);
    bool isMovePromotion(int startSquare, int targetSquare);

private:
    void freshState();
    void setBoardRotate(bool isBoardRotate);

private:
    Board* board;

    sf::Shader shader;
    sf::RenderStates state;
    Theme* theme;
    // list const squareIndex: board, analysis
    Point boardPosition;
    Point boardSize;
    Point cellSize;

private:
    std::vector<PiecePrint*> piecePrintList;
    Bot* bot;
    BoardPrint* boardPrint;
    int gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR gameResult; // 0: none, 1: white win, 2: black win, 3: draw

    std::vector<bool> isBot;
    bool isCheck;
    bool isCheckMate;
    bool isStaleMate;
    bool isWhiteTurn;
    bool isOutOfTime;

    bool isBotRunning;
    bool isEvent;

    bool isPieceSelected;
    bool isPieceHold;
    bool isPiecePromotion;
    int selectedPieceIndex;
    int holdPieceIndex;
    int preSquareIndex, curSquareIndex;
    Move movePromotion;
    Point mousePosition;

    bool isNoteHold;
    bool isBoardRotate;

    GameAttributes attributes;
    PromotionManager* promotionManager;

    std::vector<int> possibleIndexList; // all squareIndex is prepared to move
    // std::vector<int> noteCircleList;   /// all squareIndex which is right clicked
    std::vector<std::pair<int, int>> noteList; // all arrow from start to target
    std::vector<Move> movesUndoList;

    std::vector<Circle> noteCircleRender;
    std::vector<Arrow> noteArrowRender;

    std::vector<Move> suggestMoves;
};

#endif