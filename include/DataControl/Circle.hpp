#ifndef __Circle_hpp__
#define __Circle_hpp__

#include <DataControl/Color.hpp>
#include <Graphic.hpp>
#include <SFML/Graphics.hpp>

class Circle : public Graphic {
public:
    Circle(Point renderPosition);
    Circle(Point renderPosition, Point renderSize, float thickness, const ColorButMulti& colorButMulti);
    ~Circle();
    void setOutlineThickness(float outlineThickness);
    void setColorBM(const ColorButMulti& colorButMulti);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    sf::CircleShape circleShape;
    ColorButMulti colorButMulti;
    float thickness;
};

#endif