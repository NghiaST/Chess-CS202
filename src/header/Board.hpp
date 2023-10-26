#ifndef __Board_hpp__
#define __Board_hpp__

#include <SFML/Graphics.hpp>
#include "include.hpp"
#include "Graphic.hpp"

class Board : public Graphic {
private:
    sf::Texture texture;
    std::vector<sf::Texture> textureList;

public:
    Board();
    ~Board();

public: // front-end
    void preparePrint(const Theme* theme) override;  //x
    void print(sf::RenderWindow* window) override;   //x
};

#endif