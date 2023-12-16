#ifndef __BoardCustomManager_hpp__
#define __BoardCustomManager_hpp__

#include <ChessBoard/Board.hpp>
#include <ChessBoard/LogicBoard.hpp>
#include <ChessBoard/LogicBoardStandard.hpp>
#include <IngameScreen/PiecePrint.hpp>
#include <IngameScreen/BoardPrint.hpp>
#include <DataControl/Include.hpp>
#include <DataControl/TextBox.hpp>
#include <DataControl/Button.hpp>
#include <DataControl/FileManager.hpp>
#include <DataControl/GameAttributes.hpp>
#include <CustomScreen/ButtonPieceGroup.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class BoardCustomManager : public sf::Drawable, public GameAttributes {
public:
    BoardCustomManager(Point renderPosition, Point renderSize);
    ~BoardCustomManager();
    std::string handleEvent(const sf::Event& event);
    std::string update(sf::Time deltaTime);
    void updateRender();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

public:
    // Accessors
    const Board* getBoard() const;

    // Modifiers
    void setDefault();
    void setClean();
    bool isCustomBoardValid();

private:
    Board* board;
    // CustomPieceManager* pieceManager;

    sf::Shader shader;
    sf::RenderStates state;
    Theme* theme;
    // list const squareIndex: board, analysis
    Point boardPosition;
    Point boardSize;
    Point cellSize;

private:
    std::vector<PiecePrint*> piecePrintList;
    BoardPrint* boardPrint;

    bool isPieceHold;
    int selectedPieceIndex;
    Point mousePosition;

    bool mIsBoardRotate;
    ButtonPieceGroup* buttonPieceGroup;

};

#endif