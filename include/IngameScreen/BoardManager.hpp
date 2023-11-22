#ifndef __BoardManager_hpp__
#define __BoardManager_hpp__

#include <ChessBoard/Bot.hpp>
#include <ChessBoard/Board.hpp>
#include <IngameScreen/PiecePrint.hpp>
#include <IngameScreen/BoardPrint.hpp>
#include <IngameScreen/PromotionManager.hpp>
#include <DataControl/Include.hpp>
#include <DataControl/TextBox.hpp>
#include <DataControl/Button.hpp>
#include <DataControl/Arrow.hpp>
#include <DataControl/Circle.hpp>
#include <DataControl/FileInit.hpp>
#include <DataControl/GameSettings.hpp>
#include <DataControl/GameAttributes.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class BoardManager : public sf::Drawable, public GameAttributes {
public:
    enum GAMESTATUS {
        NONE = 0,
        NONSTART = 1,
        ONGOING = 2,
        ENDGAME = 3
    };
    enum ENDFLAG {
        UNKNOWN = 0,
        CHECKMATE,
        STALEMATE,
        AGREEDRAW,
        RESIGN,
        TIMEOUT,
        THREEFOLDREP,
        FIFTYMOVE,
        DEADPOSITION
    };

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
    bool isCheckMate() const;
    bool ifStaleMate() const;
    bool ifEndGame() const;
    const Board& getBoard() const;

    // Modifiers
    void NewGame();
    void Reload();
    void Undo();
    void Redo();
    void EndGame(ENDFLAG endFlag);

    void setBotHelp(bool isBotHelp);
    void setAutoRestart(bool isAutoRestart);


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
    GAMESTATUS gameStatus; // 0: none, 1: newgame, 2: ongoing, 3: endgame
    CHESS::COLOR gameResult; // 0: none, 1: white win, 2: black win, 3: draw

    std::vector<bool> isBot;
    bool mIsAutoRestart;
    bool mIsCheck;
    bool mIsCheckMate;
    bool mIsStaleMate;
    bool mIsWhiteTurn;

    bool isBotRunning;
    bool isEvent;
    ENDFLAG endFlag;

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

    // GameAttributes attributes;
    PromotionManager* promotionManager;

    std::vector<int> possibleIndexList; // all squareIndex is prepared to move
    // std::vector<int> noteCircleList;   /// all squareIndex which is right clicked
    std::vector<std::pair<int, int>> noteList; // all arrow from start to target

    std::vector<Circle> noteCircleRender;
    std::vector<Arrow> noteArrowRender;

    std::vector<Move> suggestMoves;
};

#endif