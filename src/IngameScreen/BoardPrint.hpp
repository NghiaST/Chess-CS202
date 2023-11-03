#ifndef __BoardPrint_hpp__
#define __BoardPrint_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../Graphic.hpp"
#include "../DataControl/Theme.hpp"

class BoardPrint : public Graphic {
public:
    BoardPrint(Point boardPosition = Point(0, 0), Point boardSize = Point(0, 0));
    ~BoardPrint();
    void setStateBoard(const std::vector<int>& stateBoard);
    void setStateCell(int index, int state);
    int getStateCell(int index);

public: // front-end
    void update(const Theme* theme);
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

public:
    enum STATUS {
        COMMON = 0,
        SELECTED = 1,
        PREMOVE = 2,
        POSSIBLE = 3,
        CHECK = 4,
        CHECKMATE = 5
    };
private:
    std::vector<sf::Sprite> spriteBoardList;
    std::vector<sf::Sprite> spriteBoardShaderList;
    // stateBoard[i]: STATUS::COMMON, SELECTED, POSSIBLE, POSSIBLE_CAPTURE, CHECK, CHECKMATE
    std::vector<int> stateBoard;
};

#endif