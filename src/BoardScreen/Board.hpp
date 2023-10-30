#ifndef __Board_hpp__
#define __Board_hpp__

#include <SFML/Graphics.hpp>
#include "../DataControl/Include.hpp"
#include "../Graphic.hpp"
#include "../DataControl/Theme.hpp"

class Board : public Graphic {
private:
    std::vector<sf::Sprite> spriteSquareList;
    // stateBoard[i] = 0: common, 1: selected, 2: possible move, 3: possible capture, 4: check, 5: checkmate
    std::vector<int> stateBoard;
    double sizeBoard;

public:
    Board();
    ~Board();
    void setStateBoard(const std::vector<int>& stateBoard);
    void setStateCell(int index, int state);

public: // front-end
    void update(const Theme* theme) override;
    void render(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) override;
};

#endif