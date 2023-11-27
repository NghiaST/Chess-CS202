#ifndef __Image_hpp__
#define __Image_hpp__

#include <DataControl/Include.hpp>
#include <Graphic.hpp>
#include <SFML/Graphics.hpp>

class Image : public Graphic {
public:
    Image();
    Image(const sf::Texture& texture, Point renderPosition = Point(0, 0), Point renderSize = Point(-1, -1), bool isPrint = true, int priorityPrint = 0);

    void setTexture(const sf::Texture& texture);
    void setTextureRect(sf::IntRect textureRect);
    void setRenderPositionSize(Point renderPosition, Point renderSize);
    void setRenderPosition(Point renderPosition);
    void setRenderSize(Point renderSize);

    const sf::Sprite& getSprite() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

protected:
    sf::Sprite sprite;
};

class ImageActive : public Image {
public:
    ImageActive();
    ImageActive(const sf::Texture& texture, Point renderPosition = Point(0, 0), Point renderSize = Point(-1, -1), bool isPrint = true, int priorityPrint = 0);
    void setMouseStatus(int mousestatus, Point mousePosition = Point(0, 0));
    void setMainPosition(Point mPosition);
    void setMousePosition(Point mousePosition);
    bool handleEvent(const sf::Event& event);

protected:
    sf::Sprite sprite;
    Point mPosition;
    Point mousePosition;
    MOUSE::STATUS mouseStatus;
};

#endif