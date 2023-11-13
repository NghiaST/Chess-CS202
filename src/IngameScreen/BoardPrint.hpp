#ifndef __BoardPrint_hpp__
#define __BoardPrint_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../Graphic.hpp"
#include "../DataControl/Theme.hpp"

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
    BoardPrint(Point boardPosition = Point(0, 0), Point boardSize = Point(0, 0));
    ~BoardPrint();
    void setStateBoard(const std::vector<int>& stateBoard);
    void setStateCell(int index, STATUS state);
    int getStateCell(int index);

public: // front-end
    void update(const Theme* theme);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    std::vector<sf::Sprite> spriteBoardList;
    std::vector<sf::Sprite> spriteBoardShaderList;
    // stateBoard[i]: STATUS::COMMON, SELECTED, POSSIBLE, POSSIBLE_CAPTURE, CHECK, CHECKMATE
    std::vector<int> stateBoard;
};

#endif