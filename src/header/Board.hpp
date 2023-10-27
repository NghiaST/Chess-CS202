#ifndef __Board_hpp__
#define __Board_hpp__

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Graphic.hpp"
#include "Theme.hpp"

class Board : public Graphic {
private:
    std::vector<sf::Texture> textureList;
    std::vector<sf::Sprite> spriteSquareList; 

public:
    Board();
    ~Board();

public: // front-end
    void preparePrint(const Theme* theme) override;
    void print(sf::RenderWindow* window) override;
};

#endif