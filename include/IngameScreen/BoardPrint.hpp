#ifndef __BoardPrint_hpp__
#define __BoardPrint_hpp__

#include <Graphic.hpp>
#include <DataControl/Include.hpp>
#include <DataControl/Theme.hpp>
#include <SFML/Graphics.hpp>

class BoardPrint : public Graphic {
public:
    enum STATUS {
        Common = 0,
        Hover,
        Selected,
        PreMoveStart,
        PreMoveTarget,
        Possible,
        PossibleCapture,
        Check,
        CheckMate,
        StaleMate
    };

public:
    BoardPrint(Point boardPosition, Point boardSize, const TextureBoard* TextureBoard);
    ~BoardPrint();
    void setTextureBoard(const TextureBoard* TextureBoard);
    void setStateBoard(const std::vector<int>& stateBoard);
    void setStateCell(int index, STATUS state);
    void setBoardRotate(bool mIsBoardRotate);
    int getStateCell(int index);
    int getMouseIndex(Point mousePosition, bool isGetRotate = true);

public: // front-end
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    std::vector<sf::Sprite> spriteBoardList;
    std::vector<sf::Sprite> spriteBoardShaderList;
    // stateBoard[i]: STATUS::COMMON, SELECTED, POSSIBLE, POSSIBLE_CAPTURE, CHECK, CHECKMATE
    std::vector<int> stateBoard;
    const TextureBoard* textureBoard;
    bool mIsBoardRotate;
};

#endif