#include "Image.hpp"

Image::Image() : Graphic() {}

Image::Image(const sf::Texture& texture, Point renderPosition, Point renderSize, bool isPrint, int priorityPrint) 
    : Graphic(renderPosition, renderSize, isPrint, priorityPrint)
{
    setTexture(texture);
    setRenderPositionSize(renderPosition, renderSize);
    // setRenderSize(renderSize);
    // setRenderPosition(renderPosition);
}

void Image::setTexture(const sf::Texture& texture) {
    sprite = sf::Sprite();
    sprite.setTexture(texture);
    setRenderSize(renderSize);
}

void Image::setTextureRect(sf::IntRect textureRect) {
    sprite.setTextureRect(textureRect);
}

void Image::setRenderPositionSize(Point renderPosition, Point renderSize) {
    setRenderSize(renderSize);
    setRenderPosition(renderPosition);
}

void Image::setRenderPosition(Point renderPosition) {
    Graphic::setRenderPosition(renderPosition);
    sprite.setPosition(renderPosition.to2f());
}

void Image::setRenderSize(Point renderSize) {
    Graphic::setRenderSize(renderSize);
    if (sprite.getTextureRect().width != 0 && sprite.getTextureRect().height != 0)
        sprite.setScale(renderSize.x / sprite.getTextureRect().width, renderSize.y / sprite.getTextureRect().height);
}

const sf::Sprite& Image::getSprite() const {
    return sprite;
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isPrint) {
        target.draw(sprite, states);
    }
}